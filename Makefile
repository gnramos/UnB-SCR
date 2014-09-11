# @file Makefile
# 
# @author Guilherme N. Ramos (gnramos@unb.br)
#
# - Assuming POSIX environment (for bc command).
# - Each driver should have unique name (for logging purposes)
# 
# Builds the controllers specified by DRIVERS argument and starts a simulation
# with them, considering the configuration specified in RACE_XML argument. This 
# assumes a few things:
# 1) The driver files configured for use with ClientMakefile.
# 2) The XML race file is configured properly for the number of drivers.
#
# Observations:
# 1) RACE_XML must be an absolute path to the file.
# 2) Racers will be positioned according to the order given in DRIVERS.
# 3) Multiple instances of the same driver are allowed, but logging considers the
# name only (thus all will be logged into the same file).
#
# Example:
#   make DRIVERS="SimpleDriver GrandmaDriver" RACE_XML=~/race_2.xml
#
#
# To-do
# 1) Fix need for bc command.
# 2) Log multiple instances of same driver in multiple files.

# Set starting port.
FREE_PORT ?= 3001

# Set simulator log file.
TORCS_LOG ?= TORCS

##########
# Macros #
##########

# Log date into given file.
define log_date
	@echo "***********************************" >> $1
	@date +'%y.%m.%d %H:%M:%S' >> $1
endef

# Runs the simulator for the given race, logging results into given file.
define run_server
	$(info Preparing simulation...)
	$(call log_date,$1.log)
	torcs -r $(RACE_XML) >> $1.log &
endef

# Runs the client racers, logging the results. 
define run_client
	$(call log_date,$1.log)
	./bin/$1 port:$(FREE_PORT) >> $1.log &
	$(eval FREE_PORT := $(shell echo $(FREE_PORT)+1 | bc))
endef

###########
# Targets #
###########

# Run simulation & log results.
all: test_race drivers
	$(call run_server,$(TORCS_LOG))
	$(foreach DRIVER,$(DRIVERS),$(call run_client,$(DRIVER)))

# Check for XML config file.
test_race:
ifeq (,$(wildcard $(RACE_XML)))
	$(error Config file "$(RACE_XML)" does not exist!) 
endif

# Build drivers.
drivers:
	$(foreach DRIVER, $(DRIVERS), $(MAKE) -f ClientMakefile DRIVER=$(DRIVER);)