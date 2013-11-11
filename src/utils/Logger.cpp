/** @file Logger.cpp
  *
  * Implements output routines for the drivers
  *
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */

#include <string.h>
#include "Logger.h"

/* Constructor/Destructor */
Logger::Logger ()
{
  Logger::level = Logger::LOG_DEBUG;
};

Logger::~Logger ()
{

};

// Public methods

/* Sets the verbosity */
void Logger::setLevel(int level)
{
}
  
/* Proccess a method for output */
void Logger::debug(char* message)
{
}

void Logger::info(char* message)
{
}

void Logger::error(char* message)
{
}

// Private methods

/* Output a Method */
void Logger::output(char* message)
{
}
