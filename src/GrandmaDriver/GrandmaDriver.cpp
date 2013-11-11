/** @file GrandmaDriver.cpp
  *
  * Defines the GrandmaDriver.
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  */

#include "CarControl.h"
#include "CarState.h"
#include "GrandmaDriver.h"
#include "Logger.h"

float
getAcceleration (CarState & cs)
{
  const float finalSpeedSq = GrandmaDriver::finalSpeed * GrandmaDriver::finalSpeed;
  float speedSq = cs.getSpeedX() * cs.getSpeedX() + cs.getSpeedY() * cs.getSpeedY();
  if (speedSq < 0.9 * finalSpeedSq)
    return 0.2;
  else if (speedSq > 1.1 * finalSpeedSq)
    return 0;
  return 0.1;
}

int
getGear (CarState & cs)
{
  return 1;
}

float
getSteering (CarState & cs)
{
  // based on Loiacono's SimpleDriver

  const float steerLock = 0.366519;
  float targetAngle = (cs.getAngle() - cs.getTrackPos() * 0.5) / steerLock;

  // normalize steering
  if (targetAngle < -1)
    targetAngle = -1;
  else if (targetAngle > 1)
    targetAngle = 1;

  return targetAngle;
}


GrandmaDriver::GrandmaDriver ():BaseDriver ()
{
};

GrandmaDriver::~GrandmaDriver ()
{
};

string
GrandmaDriver::drive (string sensors)
{
  CarState cs(sensors);

  
  // Example of logging output -- by Claus
  std::ostringstream ss; // Ugly voodoo for converting a number to a string
  ss << cs.getDistRaced(); // need to fix this later
  std::string s(ss.str()); // use boost, or self library.

  log.info(s);
  // Question: how do I know how long I have been racing, to add a time delay
  // for logs? (for example, log every second). Do I have to use system time?
  // Example of logging output end




  float accel = getAcceleration(cs), brake = 0, steer =
    getSteering(cs), clutch = 0;
  int gear = getGear(cs), focus = 0, meta = 0;

  CarControl cc(accel, brake, gear, steer, clutch, focus, meta);
  return cc.toString ();
}
