
/** @file PIDDriver.cpp
  *
  * Defines the PIDDriver.
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "CarControl.h"
#include "CarState.h"
#include "Logger.h"
#include "PIDDriver.h"


int
getGear(CarState & cs) {
	int current_gear = cs.getGear();
	if(!current_gear) return 1;

	if(cs.getRpm() > 8000) ++current_gear;
	else if(current_gear > 1 && cs.getRpm() < 5000) --current_gear;
	return current_gear;
}

float
getSteering(CarState & cs) {
	// based on Loiacono's SimpleDriver

	const float
	  steerLock = 0.366519;
	float
	  targetAngle = (cs.getAngle() - cs.getTrackPos() * 0.5) / steerLock;

	// normalize steering
	if(targetAngle < -1)
		targetAngle = -1;
	else if(targetAngle > 1)
		targetAngle = 1;

	return targetAngle;
}


float
getSpeed(CarState & cs) {
	return sqrt(pow(cs.getSpeedX(), 2) + pow(cs.getSpeedY(), 2));
}


/**
 * Decides whether to load a parameter file, or load default parameter values.
 */
PIDDriver::PIDDriver():BaseDriver(), speedPID(KP, KI, KD) {

  // Ugly hack: can't pass an ofstream as a paramter of a function, 
  // so we need to load it as a class attribute, and close it there after
  // we're done with it.


  /* Beware, Ugly hacks ahead:
   * 
   * Hack 1: Ideally, we want the filename to be passed as a parameter.
   * But this requires changing client.cpp and Basedriver.h
   * For now, we use a fixed file name string.
   * 
   * Hack 2: C++ doesn't seem to like passing file streams as function 
   * parameters. So the input file is stored as a class attribute. Probably 
   * there is a more proper way to do this.
   */
  param_stream.open ("parameter.par", ios::in); 

  // test if the parameter file was found
  if (param_stream.is_open()) {
    log.info("Loading Parameters from file");
    loadParameterFile();
    param_stream.close();
  } else {
    log.info("Loading Default Parameters");
    loadParameterDefault();
  }
};

/**
 * load parameter values from a file
 *
 * @TODO: This statically loads parameters in a fixed order inside the 
 * file ("param1,param2,param3"). We probably want to change it to be a bit 
 * more smart and flexible ("paramname=paramvalue", one per line, 
 * or maybe read some xml file format)
 *
 */
void
PIDDriver::loadParameterFile() {
  string item;
  std::vector<string> params;


  while (getline(param_stream,item,',')) { 
    params.push_back(item);
  }

  finalSpeed = atof(params[0].c_str());
  speedPID.set(atof(params[1].c_str()), 
	       atof(params[2].c_str()),
	       atof(params[3].c_str()));

}

/**
 * load default values for the parameters
 */
void
PIDDriver::loadParameterDefault() {
  finalSpeed = 160;
  speedPID.set(0.1,0.01,0.005);
}


PIDDriver::~PIDDriver()
{
};

string
PIDDriver::drive(string sensors) {
	CarState cs(sensors);

	float brake = 0, steer = getSteering(cs), clutch = 0;

	float accel = speedPID.output(finalSpeed, getSpeed(cs), PID_DT);

	int gear = getGear(cs), focus = 0, meta = 0;

	CarControl cc(accel, brake, gear, steer, clutch, focus, meta);

	return cc.toString();
}
