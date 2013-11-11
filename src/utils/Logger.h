/** @file Logger.h
  *
  * Implements output for drivers
  *
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  * @author Guilherme N. Ramos (gnramos@unb.br)
  */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

/** Logs information. */
class Logger {
 public:
  /** Log levels. */
	enum Level {
	Debug = 0, /**< Log everything. */ 
	Info = 1,  /**< Log performance/evaluation. */ 
	Error = 2  /**< Log error/warnings only. */ 
 };
 protected:
  Level level;

 public:
  /** Constructor. */
  Logger();
  
  /** Destructor. (Close output files) */
  ~Logger();

  /** Sets the verbosity */
  void setLevel(Level level); 
  
  /** Output a message */
  void debug(string message);
  
  /** Output a message */
  void info(string message);
  
  /** Output a message */
  void error(string message);

 protected:
  void output(string message);
};

#endif				/* LOGGER_H */
