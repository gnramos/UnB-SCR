/** @file PIDDriver.cpp
  *
  * Defines the PIDDriver.
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */

#include <math.h>
#include <fstream>

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

    char paramFile[] =
        "/home/gnramos/Documents/Dropbox/CIC/Dropbox/workspace/TORCS/mult/data/parameter.par";

    float final_speed, p, i, d;
  

    /**
    * load parameter values from a file
    *
    * @TODO: This statically loads parameters in a fixed order inside the 
    * file ("param1,param2,param3"). We probably want to change it to be a bit 
    * more smart and flexible ("paramname=paramvalue", one per line, 
    * or maybe read some xml file format)
    */
    std::ifstream ifs;
    ifs.open(paramFile, std::ifstream::in);
    if (ifs.is_open()) {
        log.info("Loading parameters from file.");
        ifs >> final_speed >> p >> i >> d;
    } else {
        log.info("Loading default parameters.");
        final_speed = FINAL_SPEED, p = KP, i = KI, d = KD;
    }
    ifs.close();

    finalSpeed = final_speed;
    speedPID.set(p, i, d);
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
