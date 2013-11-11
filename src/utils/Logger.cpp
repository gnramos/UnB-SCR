/** @file Logger.cpp
  *
  * Implements output routines for the drivers
  *
  * @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
  */


#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;

/* Constructor/Destructor */
Logger::Logger ()
{
  level = Logger::LOG_DEBUG;
};

Logger::~Logger ()
{
  // close any open files.
};

// Public methods

/* Sets the verbosity */
void Logger::setLevel(int l)
{
  level = l;
}
  
/* Parse a message for output */
// TODO: decouple the variables and tags a bit more
void Logger::debug(string message)
{
  if (level <= Logger::LOG_DEBUG)
    {
      string aux = "[DEBUG] " + message;
      output(aux);
    }
}

void Logger::info(string message)
{
  if (level <= Logger::LOG_INFO)
    {
      string aux = "[INFO] " + message;
      output(aux);
    }
}

void Logger::error(string message)
{
  if (level <= Logger::LOG_ERROR)
    {
      string aux = "[ERROR] " + message;
      output(aux);
    }
}

// Private methods

/* Output a message that has been parsed */
void Logger::output(string message)
{
  
  /* TODO: Send the output to an open 
     file or some other description, depending 
     on the parameter values */  
  cout << message << endl;
}
