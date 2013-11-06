/** @file GrandmaDriver.h
  *
  * Describes the GrandmaDriver.
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  */

#ifndef GRANDMA_DRIVER_H
#define GRANDMA_DRIVER_H

#include <string.h>
#include "BaseDriver.h"
#include "IO.h"

/** A stupidly simple controller that tries to keep a constant speed while 
 * staying in the middle of the track. */
class GrandmaDriver:public BaseDriver {
 private:
	static const float finalSpeed = 50;	     /**< Final constant speed. */

 public:
	/** Constructor. */
	 GrandmaDriver();

	/** Destructor. */
	virtual ~ GrandmaDriver();

	/** Driving function.
	 * @param sensors the current world state.
	 * @return a string representing the controlling action to perform. */
	virtual string drive(string sensors);

	float getAcceleration(const Sensors & s);

	int getGear(const Sensors & s);

	float getSteering(const Sensors & s);
};

#endif				/* GRANDMA_DRIVER_H */
