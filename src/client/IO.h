
/** @file IO.h
 * Defines the input/output for the controllers. Based on Loiacono's CarState/CarControl
 * classes.
 *
 * @author Guilherme N. Ramos (gnramos@unb.br)
 */

#ifndef TORCS_IO_H
#define TORCS_IO_H

#include "SimpleParser.h"

	/** Defines the sensors according to Tables 1/2 in the manual. */
class Sensors {
 private:
	static const int NumberOfFocusSensors = 5;
	static const int NumberOfTrackSensors = 19;
	static const int NumberOfOpponentsSensors = 36;
 public:
	float angle;	     /**< Angle between the car direction and the direction of the track axis. Range [-PI,PI] rad. */
	float curLapTime;	  /**< Time (s) elapsed during current lap. Range [0,INF). */
	float damage;	      /**< Current damage of the car (the higher is the value the higher is the damage). Range [0, INF). */
	float distFromStart;	     /**< Distance (m) of the car from the start line along the track line. Range [0, INF). */
	float distRaced;	 /**< Distance (m) covered by the car from the beginning of the race. */
	float focus[NumberOfFocusSensors];	   /**< Current fuel level. */
	float fuel;
	int gear;	    /**< Current gear: -1 is reverse, 0 is neutral and the gear from 1 to 6. */
	float lastLapTime;	   /**< Time (s) to complete the last lap. Range [0, INF). */
	float opponents[NumberOfOpponentsSensors];
	int racePos;	       /**< Position in the race with respect to other cars. Range [1, N]. */
	int rpm;	   /**< Number of rotations per minute of the car engine. Range [0, INF). */
	float speedX;	      /**< Speed (km/h) of the car along the longitudinal axis of the car. Range (-INF, INF). */
	float speedY;	      /**< Speed (km/h) of the car along the transverse axis of the car. Range (-INF, INF). */
	float speedZ;	      /**< Speed (km/h) of the car along the Z axis of the car. Range (-INF, INF). */
	float track[NumberOfTrackSensors];	   /**< Distance (m) between the car and the track axis. Range [0,200].*/
	float trackPos;		/**< Distance between the car and the track axis. Range (-INF, INF). */
	float wheelSpinVel[4];	       /**< Vector of 4 sensors representing the rotation speed (rad/s) of wheels. Range [0, INF). */
	float z;	 /**< Distance (m) of the car mass center from the surface of the track along the Z axis. Range (-INF, INF). */

	 Sensors(string sensors) {
		SimpleParser::parse(sensors, "angle", this->angle);
		SimpleParser::parse(sensors, "curLapTime", this->curLapTime);
		SimpleParser::parse(sensors, "damage", this->damage);
		SimpleParser::parse(sensors, "distFromStart",
				    this->distFromStart);
		SimpleParser::parse(sensors, "distRaced", this->distRaced);
		SimpleParser::parse(sensors, "focus", this->focus,
				    NumberOfFocusSensors);
		SimpleParser::parse(sensors, "fuel", this->fuel);
		SimpleParser::parse(sensors, "gear", this->gear);
		SimpleParser::parse(sensors, "lastLapTime", this->lastLapTime);
		SimpleParser::parse(sensors, "opponents", this->opponents,
				    NumberOfOpponentsSensors);
		SimpleParser::parse(sensors, "racePos", this->racePos);
		SimpleParser::parse(sensors, "rpm", this->rpm);
		SimpleParser::parse(sensors, "speedX", this->speedX);
		SimpleParser::parse(sensors, "speedY", this->speedY);
		SimpleParser::parse(sensors, "speedZ", this->speedZ);
		SimpleParser::parse(sensors, "track", this->track,
				    NumberOfTrackSensors);
		SimpleParser::parse(sensors, "trackPos", this->trackPos);
		SimpleParser::parse(sensors, "wheelSpinVel", this->wheelSpinVel,
				    4);
		SimpleParser::parse(sensors, "z", this->z);
}};

	/** Defines the effectors according to Table 3 in the manual. */
class Effectors {
 public:
	float accel;	     /**< Virtual gas pedal. Range [0,1] (0 means no gas, 1 full gas). */
	float brake;	     /**< Virtual brake pedal. Range (0 means no brake, 1 full brake). */
	float clutch;	      /**< Virtual clutch pedal. Range [0,1]  (0 means no clutch, 1 full clutch). */
	int gear;	  /**< Gear value. Range [-1,6] (-1 means reverse, 0 means neutral, 1-6 means the gear number). */
	float steer;	     /**< Steering value. Range [-1,1], -1 and +1 means respectively full right and left, that corresponds to an angle of 0.366519 rad. */
	int focus;	   /**< Focus direction (see the focus sensors in Table 1) in degrees. Range [-90,90]. */
	int meta;	  /**< This is meta-control command: 0 do nothing, 1 ask competition server to restart the race. */

		/** Constructor. */
	 Effectors(string sensors) {
		fromString(sensors);
	}
		/** Constructor. */
	    Effectors(float accel, float brake, int gear, float steer,
	      float clutch,
		      int focus = 0, int meta = 0) {
		this->accel = accel;
		this->brake = brake;
		this->gear = gear;
		this->steer = steer;
		this->clutch = clutch;
		this->focus = focus;
		this->meta = meta;
	}

	string toString() {
		string str;

		str = SimpleParser::stringify("accel", accel)
		    + SimpleParser::stringify("brake", brake)
		    + SimpleParser::stringify("gear", gear)
		    + SimpleParser::stringify("steer", steer)
		    + SimpleParser::stringify("clutch", clutch)
		    + SimpleParser::stringify("focus", focus)
		    + SimpleParser::stringify("meta", meta);

		return str;
	}

	void fromString(string sensors) {
		if (!SimpleParser::parse(sensors, "accel", accel))
			accel = 0;
		if (!SimpleParser::parse(sensors, "brake", brake))
			brake = 0;
		if (!SimpleParser::parse(sensors, "gear", gear))
			gear = 1;
		if (!SimpleParser::parse(sensors, "steer", steer))
			steer = 0;
		if (!SimpleParser::parse(sensors, "clutch", clutch))
			clutch = 0;
		if (!SimpleParser::parse(sensors, "meta", meta))
			meta = 0;
		if (!SimpleParser::parse(sensors, "focus", focus))
			focus = 0;
		if (focus < -90 || focus > 90)
			focus = 360;
	}

	// meta-command value for race restart
	// static int META_RESTART;
};

// }                            // namespace TORCS

#endif				/* TORCS_IO_H */
