# @file Makefile
# 
# @author Guilherme N. Ramos
# 
# Builds the driver specified by DRIVER_CLASS. This assumes a few things:
# 1) The files are set in the src/DRIVER_CLASS directory.
# 2) The driver files are DRIVER_CLASS.h & DRIVER_CLASS.cpp.
# 
# The idea is to create .o files and the executable file in the /bin directory.
# 

#Put here the name of your driver class
DRIVER_CLASS = GrandmaDriver

# Add compilation flags (release versions should use only -Wall).
CPPFLAGS = -Wall
#CPPFLAGS = -Wall -g -D __UDP_CLIENT_VERBOSE__

################################################################################
# The rest should work automagically...
CC =  g++

TARGET_DIR = ../../bin

DRIVER_INCLUDE = '"../$(DRIVER_CLASS)/$(DRIVER_CLASS).h"'
DRIVER_OBJECT = $(DRIVER_CLASS).o

EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER_CLASS) -D __DRIVER_INCLUDE__=$(DRIVER_INCLUDE)

CLIENT_INCLUDE = ../client
CLIENT_OBJECTS = CarControl.o CarState.o SimpleParser.o
CLIENT_SRC = $(CLIENT_INCLUDE)/client.cpp

OBJS = $(CLIENT_OBJECTS) $(DRIVER_OBJECT)
OBJS := $(addprefix $(TARGET_DIR)/,$(OBJS))

# Targets
all: $(CLIENT_OBJECTS) $(DRIVER_OBJECT) $(DRIVER_CLASS)

$(CLIENT_OBJECTS): %.o: $(CLIENT_INCLUDE)/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $(TARGET_DIR)/$@

$(DRIVER_OBJECT): $(DRIVER_CLASS).cpp
	$(CC) -c $(CPPFLAGS) -I$(CLIENT_INCLUDE) $(DRIVER_CLASS).cpp -o $(TARGET_DIR)/$(DRIVER_OBJECT)

$(DRIVER_CLASS): $(OBJS) $(CLIENT_SRC)
	$(CC) $(CPPFLAGS) $(EXTFLAGS) -I$(CLIENT_INCLUDE) $(CLIENT_SRC) -o $(TARGET_DIR)/$(DRIVER_CLASS) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET_DIR)/$(DRIVER_CLASS)