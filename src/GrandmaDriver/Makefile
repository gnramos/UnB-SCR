# GrandmaDriver Makefile
# 
# Adapted from SimpleDriver

CC            =  g++
CPPFLAGS      = -Wall -g 

# Uncomment the following line for a verbose client
#CPPFLAGS      = -Wall -g -D __UDP_CLIENT_VERBOSE__

#Put here the name of your driver class
DRIVER_CLASS = GrandmaDriver
CLIENT_INCLUDE = ../client
CLIENT_SRC = $(CLIENT_INCLUDE)/SimpleParser.cpp $(CLIENT_INCLUDE)/CarState.cpp $(CLIENT_INCLUDE)/CarControl.cpp $(CLIENT_INCLUDE)/client.cpp

#Put here the filename of your driver class header 
DRIVER_INCLUDE = '"../$(DRIVER_CLASS)/$(DRIVER_CLASS).h"' 
EXEC = $(DRIVER_CLASS)_client
SRC = $(CLIENT_SRC) $(DRIVER_CLASS).cpp

EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER_CLASS) -D __DRIVER_INCLUDE__=$(DRIVER_INCLUDE)

all: $(EXEC)

$(EXEC):
	$(CC) $(CPPFLAGS) $(EXTFLAGS) $(SRC) -o $(EXEC) -I$(CLIENT_INCLUDE)

clean:
	rm $(EXEC)




# # ga_driver Makefile
# # 
# # Copied from SimpleDriver

# CC            =  g++
# CPPFLAGS      = -Wall -g 

# # Uncomment the following line for a verbose client
# #CPPFLAGS      = -Wall -g -D __UDP_CLIENT_VERBOSE__

# #Put here the name of your driver class
# DRIVER_CLASS = GrandmaDriver
# #Put here the filename of your driver class header 
# DRIVER_INCLUDE = '"../$(DRIVER_CLASS)/$(DRIVER_CLASS).h"' 
# DRIVER_OBJ = $(DRIVER_CLASS).o
# EXEC = $(DRIVER_CLASS)_client
# CLIENT_INCLUDE = $(CLIENT_INCLUDE)

# EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER_CLASS) -D __DRIVER_INCLUDE__=$(DRIVER_INCLUDE)

# CLIENT_OBJECTS = CarControl.o CarState.o SimpleParser.o

# all: $(EXEC)

# CarControl.o:
#	$(CC) $(CPPFLAGS) $(CLIENT_INCLUDE)/CarControl.cpp -o $(CLIENT_INCLUDE)/CarControl.o -I$(CLIENT_INCLUDE) -c

# CarState.o:
#	$(CC) $(CPPFLAGS) $(CLIENT_INCLUDE)/CarState.cpp -o $(CLIENT_INCLUDE)/CarState.o -I$(CLIENT_INCLUDE) -c

# SimpleParser.o:
#	$(CC) $(CPPFLAGS) $(CLIENT_INCLUDE)/SimpleParser.cpp -o $(CLIENT_INCLUDE)/SimpleParser.o -I$(CLIENT_INCLUDE) -c

# $(EXEC): $(CLIENT_OBJECTS) $(CLIENT_INCLUDE)/client.cpp $(DRIVER_CLASS).cpp
#	$(CC) $(CPPFLAGS) $(EXTFLAGS) $(CLIENT_INCLUDE)/client.cpp $(DRIVER_CLASS).cpp -o $(EXEC) -I$(CLIENT_INCLUDE)

# clean:
#	rm -f $(CLIENT_INCLUDE)/*.o *.o $(EXEC)