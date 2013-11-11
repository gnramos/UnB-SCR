/** @file Logger.h
  *
  * Implements output for drivers
  *
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */

#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>

/** A stupidly simple controller that tries to keep a constant speed while 
 * staying in the middle of the track. */
class Logger {
 public:
  /* Log Levels */
  static const int LOG_DEBUG = 0; // Everything
  static const int LOG_INFO = 1; // Performance/Evaluation
  static const int LOG_ERROR = 2; // Error/warnings only
 protected:
  int level;

 public:
  /** Constructor. */
  Logger();
  
  /** Destructor. (Close output files) */
  ~ Logger();

  /* Sets the verbosity */
  void setLevel(int level); 
  
  /* Output a message */
  void debug(char* message);
  void info(char* message);
  void error(char* message);

 protected:
  void output(char* message);
};

#endif				/* LOGGER_H */
