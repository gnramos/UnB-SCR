CC            =  g++
CPPFLAGS      = -Wall -g 

client_objects: CarControl.o CarState.o SimpleParser.o

.SUFFIXES : .o .cpp .c

.cpp.o :
	$(CC) $(CPPFLAGS) $(EXTFLAGS) -c $<