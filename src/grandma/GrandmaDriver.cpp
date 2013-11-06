/** @file GrandmaDriver.cpp
  *
  * Defines the GrandmaDriver.
  *
  * @author Guilherme N. Ramos (gnramos@unb.br)
  */

#include "GrandmaDriver.h"

GrandmaDriver::GrandmaDriver ():BaseDriver ()
{
};

GrandmaDriver::~GrandmaDriver ()
{
};

string
GrandmaDriver::drive (string sensors)
{
  Sensors s (sensors);

  float accel = getAcceleration (s), brake = 0, steer =
    getSteering (s), clutch = 0;
  int gear = getGear (s), focus = 0, meta = 0;

  Effectors ef (accel, brake, gear, steer, clutch, focus, meta);
  return ef.toString ();
}

float
GrandmaDriver::getAcceleration (const Sensors & s)
{
  const float finalSpeedSq = finalSpeed * finalSpeed;
  float speedSq = s.speedX * s.speedX + s.speedY * s.speedY;
  if (speedSq < 0.9 * finalSpeedSq)
    return 0.2;
  else if (speedSq > 1.1 * finalSpeedSq)
    return 0;
  return 0.1;
}

int
GrandmaDriver::getGear (const Sensors & s)
{
  return 1;
}

float
GrandmaDriver::getSteering (const Sensors & s)
{
  // based on Loiacono's SimpleDriver

  const float steerLock = 0.366519;
  float targetAngle = (s.angle - s.trackPos * 0.5) / steerLock;

  // normalize steering
  if (targetAngle < -1)
    targetAngle = -1;
  else if (targetAngle > 1)
    targetAngle = 1;

  return targetAngle;
}
