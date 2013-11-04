# target
# 
# dependencies
# 
# instructions

# SOLIBRARY = libtti.so
# SOURCES   = tti.cpp  SimpleParser.cpp WrapperBaseDriver.cpp CarControl.cpp CarState.cpp RaceSet.cpp

# EXPDIR  = include

# EXPORTS = tti.h WrapperBaseDriver.h RaceSet.h Client.h CarControl.h CarState.h SimpleParser.h BaseDriver.h

# include ${MAKE_DEFAULT}

# LDFLAGS += -std=c++11 -pthread
# CXXFLAGS += -std=c++11 -pthread
# CFLAGSD += -std=c++11 -pthread

INC_DIR = include
HEADERS = ga.h SimpleDriver.h
SOURCES = src/test.cpp

CC = g++
CXXFLAGS += -Wall -g -std=c++0x -I$(INC_DIR)

INC = $(patsubst %,$(INC_DIR)/%,$(HEADERS))

all: ga

ga: $(SOURCES) $(INC)
	$(CC) $(CXXFLAGS) $(SOURCES) -o bin/ga

doc:
	doxygen Doxyfile

clean:
	rm -f *.o bin/ga