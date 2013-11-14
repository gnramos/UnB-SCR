
/** @file PIDDriver.h
  *
  * Describes the PIDDriver. 
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
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

#define KP 0.1   /** @todo Definir corretamente */
#define KI 0.01  /** @todo Definir corretamente */
#define KD 0.005 /** @todo Definir corretamente */

class PIDDriver:public BaseDriver {
  public:

	static const float finalSpeed = 100;		 /**< Final constant speed. */
	PIDController speedPID;

  public:

	/** Constructor. */
	PIDDriver();

	/** Destructor. */
	virtual ~ PIDDriver();

	/** Driving function.
	 * @param sensors the current world state.
	 * @return a string representing the controlling action to perform. */
	virtual string drive(string sensors);
};

#endif /* PID_DRIVER_H */
