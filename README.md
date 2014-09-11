UnB-SCR
=======
For lack of a better name, this project is currently called _UnB-SCR_.

Description
-----------

An attempt to evolve TORCS controller(s).

Installation
------------

As per the "Simulated Car Racing Championship Competition Software Manual" 
([v2 - April 2013](http://arxiv.org/pdf/1304.1672v2)), install TORCS 1.3.6.

Download this project's files anywhere you want them (say, "```~/workspace"```), 
the client works through UDP.

Usage
-----

Depends on what you want...

If you only want to build the client driver, its the ClientMakefile, if you want
a full simulation, see regular Makefile

### ClientMakefile

The "src/client" contains Loiacono's client files, which are essential to build 
your client - let's call him _EasyDriver_. So you should create the "EasyDriver"
directory in the "src" folder and put your controller files (```EasyDriver.h``` and 
```EasyDriver.cpp``` there). Basically, EasyDriver must inherit BaseDriver and 
implement the "drive" function (see the manual for simulation I/O details). After
that, just run "```make client DRIVER=EasyRider```" and you'll get your client 
executable for TORCS simulations.

To check if it's working, just run TORCS, configure a race in which a driver is
_scr_server_ driver and then run the executable file you created. You can test 
this with SCR's _SimpleDriver_ files that come with this project as follows:

    $ make client DRIVER=SimpleDriver
    $ torcs &

And then (assuming you started a properly configured race):

    ./bin/SimpleDriver

### Makefile

Assuming the drivers are compiled according to the ClientMakefile scheme, this 
builds the controllers specified by DRIVERS argument and starts a simulation
with them, considering the configuration specified in RACE_XML argument. 

For example:

    $ make DRIVERS="SimpleDriver EasyRider" RACE_XML=~HOME/.torcs/race_2.xml

Observations
------------

To run TORCS in text-mode, the XML configuration file must be given with absolute path.
