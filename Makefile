# @file Makefile
# 
# @author Claus Aranha (caranha@cs.tsukuba.ac.jp)
# @author Guilherme N. Ramos (gnramos@unb.br)
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
#   ./bin/SimpleDriverClient


# Set compilation flags.
CXXFLAGS = -Wall
#CXXFLAGS = -Wall -g -D __UDP_CLIENT_VERBOSE__
# UDP Client (in client.cpp) flags.
EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER) -D __DRIVER_INCLUDE__='"$(DRIVER).h"'

# Set the compiler.
CC =  g++

# Set where to put the .o and executable files.
TARGET_DIR = bin
SRC_DIR = src

# Set variables according to the driver.
DRIVER_DIR    = $(SRC_DIR)/$(DRIVER)
DRIVER_SRC    = $(DRIVER_DIR)/$(DRIVER).cpp
DRIVER_OBJ    = $(DRIVER).o
DRIVER_TARGET = $(DRIVER)Client

# Set client variables.
UDP_CLIENT_DIR   = $(SRC_DIR)/client
UDP_CLIENT_SRC   = $(UDP_CLIENT_DIR)/client.cpp
UDP_CLIENT_OBJS := $(wildcard $(UDP_CLIENT_DIR)/*.cpp)
UDP_CLIENT_OBJS := $(filter-out $(UDP_CLIENT_SRC), $(UDP_CLIENT_OBJS))
UDP_CLIENT_OBJS := $(notdir $(UDP_CLIENT_OBJS:.cpp=.o))

# Auxiliary objects.
UTILS_DIR   = $(SRC_DIR)/utils
UTILS_SRC  := $(wildcard $(UTILS_DIR)/*.cpp)
UTILS_OBJS := $(notdir $(UTILS_SRC:.cpp=.o))

OBJS = $(UTILS_OBJS) $(UDP_CLIENT_OBJS) $(DRIVER_OBJ)
OBJS := $(addprefix $(TARGET_DIR)/,$(OBJS))

###########
# Targets #
###########
all: test_$(DRIVER) $(TARGET_DIR) $(DRIVER_TARGET)

# Check driver argument.
test_$(DRIVER):
ifndef DRIVER
	$(error you must define the DRIVER argument! For example: "make DRIVER=SimpleDriver")
else
	$(info Creating $(DRIVER_TARGET).)
endif

# Build UDP client objects.
$(UDP_CLIENT_OBJS): %.o: $(UDP_CLIENT_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $(TARGET_DIR)/$@

# Build auxiliary objects.
$(UTILS_OBJS): %.o: $(UTILS_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $(TARGET_DIR)/$@

# Build driver object.
$(DRIVER_OBJ): $(UTILS_OBJS) $(DRIVER_SRC) 
	$(CC) -c $(CXXFLAGS) -I$(UDP_CLIENT_DIR) -I$(UTILS_DIR) -I$(DRIVER_DIR) $(DRIVER_SRC) -o $(TARGET_DIR)/$(DRIVER_OBJ)

# Build driver client. 
$(DRIVER_TARGET): $(OBJS) $(DRIVER_OBJ) $(UDP_CLIENT_SRC)
	$(CC) $(CXXFLAGS) $(EXTFLAGS) -I$(UTILS_DIR) -I$(UDP_CLIENT_DIR) -I$(DRIVER_DIR) $(UDP_CLIENT_SRC) -o $(TARGET_DIR)/$(DRIVER_TARGET) $(OBJS)

# Build target directory.
$(TARGET_DIR):
	mkdir $(TARGET_DIR)

# Cleanup.
clean:
	rm -f $(TARGET_DIR)/*