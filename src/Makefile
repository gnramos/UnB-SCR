# @file Makefile
# 
# @author Guilherme N. Ramos
# 
# Builds the controller specified by DRIVER argument. This assumes a few things:
# 1) The files are set in the src/DRIVER directory.
# 2) The controller files are DRIVER.h & DRIVER.cpp (extra .h files within the
# folder should work, but any more .cpp files will break things).
# 
# The idea is to create .o files and the executable file in the /bin directory.
# After all is done, just start the TORCS server and run the executable to see
# your client race. In theory, everything should work automagically...
# 
# Example (assuming you have TORCS running with a race waiting for the clients:
#   make DRIVER=SimpleDriver
#   ./../bin/SimpleDriver


# Add compilation flags.
CPPFLAGS = -Wall
#CPPFLAGS = -Wall -g -D __UDP_CLIENT_VERBOSE__

# Set the compiler.
CC =  g++

# Set where to put the .o and executable files.
TARGET_DIR = ../bin

# Set variables according to the driver.
DRIVER_CLASS = $(DRIVER)
DRIVER_INCLUDE = $(DRIVER_CLASS)
DRIVER_HEADER = '"../$(DRIVER_INCLUDE)/$(DRIVER_CLASS).h"'
DRIVER_SRC = $(DRIVER_INCLUDE)/$(DRIVER).cpp
DRIVER_OBJECT = $(DRIVER_CLASS).o

# Set client variables.
CLIENT_INCLUDE = client
CLIENT_OBJECTS = CarControl.o CarState.o SimpleParser.o WrapperBaseDriver.o
CLIENT_SRC = $(CLIENT_INCLUDE)/client.cpp
OBJS = $(CLIENT_OBJECTS) $(DRIVER_OBJECT)
OBJS := $(addprefix $(TARGET_DIR)/,$(OBJS))

# Set variables accordingly so client.cpp works
EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER) -D __DRIVER_INCLUDE__=$(DRIVER_HEADER)

# Targets
all: test_$(DRIVER) $(CLIENT_OBJECTS) $(DRIVER_OBJECT) $(DRIVER)

$(CLIENT_OBJECTS): %.o: $(CLIENT_INCLUDE)/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $(TARGET_DIR)/$@

$(DRIVER_OBJECT): $(DRIVER_SRC)
	$(CC) -c $(CPPFLAGS) -I$(CLIENT_INCLUDE) $(DRIVER_INCLUDE) $(DRIVER_SRC) -o $(TARGET_DIR)/$(DRIVER_OBJECT)

$(DRIVER): $(CLIENT_OBJECTS) $(DRIVER_OBJECT) $(CLIENT_SRC)
	$(CC) $(CPPFLAGS) $(EXTFLAGS) -I$(CLIENT_INCLUDE) $(CLIENT_SRC) -o $(TARGET_DIR)/$(DRIVER) $(OBJS)

test_$(DRIVER):
ifndef DRIVER
	$(error you must define the DRIVER argument! For example: "make DRIVER=SimpleDriver")
else
	$(info Creating $(DRIVER))
endif

clean:
	rm -f $(TARGET_DIR)/*