# ga_driver Makefile
# 
# Copied from SimpleDriver

CC            =  g++
CPPFLAGS      = -Wall -g 

# Uncomment the following line for a verbose client
#CPPFLAGS      = -Wall -g -D __UDP_CLIENT_VERBOSE__

CLIENT_INCLUDE = ../client

#Put here the name of your driver class
DRIVER_CLASS = GrandmaDriver
#Put here the filename of your driver class header 
DRIVER_INCLUDE = '"$(DRIVER_CLASS).h"' 
DRIVER_OBJ = $(DRIVER_CLASS).o

EXTFLAGS = -D __DRIVER_CLASS__=$(DRIVER_CLASS) -D __DRIVER_INCLUDE__=$(DRIVER_INCLUDE)

OBJECTS = $(CLIENT_INCLUDE)/SimpleParser $(DRIVER_OBJ)

all: $(OBJECTS) client


.SUFFIXES : .o .cpp

.cpp.o :
	$(CC) $(CPPFLAGS) -I $(CLIENT_INCLUDE) $(EXTFLAGS) -c $<


client: client.cpp $(OBJECTS)
		$(CC) $(CPPFLAGS) $(EXTFLAGS) -o client client.cpp $(OBJECTS) -I $(CLIENT_INCLUDE)

clean:
	rm -f *.o client  
