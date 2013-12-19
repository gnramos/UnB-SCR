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
#   make client DRIVER=SimpleDriver
#   ./bin/SimpleDriverClient

# Set the compiler.
CC =  g++

# Set compilation flags.
CXXFLAGS = -Wall
#CXXFLAGS = -Wall -g -D __UDP_CLIENT_VERBOSE__
# UDP Client (in client.cpp) flags.
EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER) -D __DRIVER_INCLUDE__='"$(DRIVER).h"'

# Set source and target dirs.
TARGET_DIR = bin
SRC_DIR = src

# Client source files.
UDP_CLIENT_DIR  = $(SRC_DIR)/client
UDP_CLIENT_SRC  = $(wildcard $(UDP_CLIENT_DIR)/*.cpp)
UDP_CLIENT_MAIN = $(UDP_CLIENT_DIR)/client.cpp
UDP_CLIENT_SRC := $(filter-out $(UDP_CLIENT_MAIN), $(UDP_CLIENT_SRC))

# Driver source files.
DRIVER_DIR    = $(SRC_DIR)/$(DRIVER)
DRIVER_SRC    = $(wildcard $(DRIVER_DIR)/*.cpp)
DRIVER_SRC   := $(DRIVER_SRC) $(UDP_CLIENT_MAIN)
DRIVER_TARGET = $(DRIVER)Client

# Auxiliary source files.
UTILS_DIR   = $(SRC_DIR)/utils
UTILS_SRC  = $(wildcard $(UTILS_DIR)/*.cpp)

# Setup objects.
UDP_CLIENT_OBJS := $(notdir $(UDP_CLIENT_SRC:.cpp=.o))
UTILS_OBJS      := $(notdir $(UTILS_SRC:.cpp=.o))
DRIVER_OBJS      = $(UDP_CLIENT_OBJS) $(UTILS_OBJS)
DRIVER_OBJS     := $(addprefix $(TARGET_DIR)/,$(DRIVER_OBJS))

###########
# Targets #
###########

# Build driver client.
client: | target_dir $(DRIVER_TARGET)

# Check driver argument.
test_$(DRIVER):
ifndef DRIVER
	$(error you must define the DRIVER argument! For example: "make client DRIVER=SimpleDriver")
else
	$(info Creating $(DRIVER_TARGET).)
endif

# Build UDP client objects.
$(UDP_CLIENT_OBJS): %.o : $(UDP_CLIENT_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $(TARGET_DIR)/$@

# Build auxiliary objects.
$(UTILS_OBJS): %.o : $(UTILS_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $(TARGET_DIR)/$@

# Build driver object.
$(DRIVER_TARGET): test_$(DRIVER) $(DRIVER_SRC) $(UDP_CLIENT_OBJS) $(UTILS_OBJS)
	$(CC) $(CXXFLAGS) $(EXTFLAGS) $(DRIVER_SRC) -I$(UDP_CLIENT_DIR) -I$(UTILS_DIR) -I$(DRIVER_DIR) -o $(TARGET_DIR)/$(DRIVER_TARGET) $(DRIVER_OBJS)

# Build target directory.
target_dir:
	@mkdir -p $(TARGET_DIR)

# Cleanup.
clean:
	rm -rf $(TARGET_DIR)
	find . -name "*~" -exec rm {} \;
	find . -name "*.o" -exec rm {} \;