
/** @file PIDDriver.h
  *
  * Describes the PIDDriver. 
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */

#ifndef PID_DRIVER_H
#define PID_DRIVER_H

#include <string.h>
#include "BaseDriver.h"
#include "SimpleParser.h"

#include "PID.h"

// http://torcs.sourceforge.net/index.php?name=Sections&op=viewarticle&artid=30#c6_6
// The robots are called all 0.02s (50Hz), do not confuse this with the physics/raceengine simulation timestep which is 0.002s (500Hz).
#define PID_DT 0.02
  /** @todo verificar se este valor está correto. */

#define FINAL_SPEED 160 /** @todo Definir corretamente */
#define KP 0.1   /** @todo Definir corretamente */
#define KI 0.01  /** @todo Definir corretamente */
#define KD 0.005 /** @todo Definir corretamente */

class PIDDriver:public BaseDriver {
  public:

  float finalSpeed;	/** Target Speed **/
  PIDController speedPID;

  public:

	/** Constructor. */
	PIDDriver(float final_speed = FINAL_SPEED);

	/** Destructor. */
	virtual ~PIDDriver();

	/** Driving function.
	 * @param sensors the current world state.
	 * @return a string representing the controlling action to perform. */
	virtual string drive(string sensors);
};

#endif /* PID_DRIVER_H */
