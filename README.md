TORCS

* Description

An attempt to evolve TORCS controller(s).

* Installation

As per the "Simulated Car Racing Championship Competition Software Manual" (v2 - 
April 2013 - http://arxiv.org/pdf/1304.1672v2), install TORCS 1.3.4.

Download this project's files anywhere you want them (say, "~/workspace"), the 
client works through UDP.

* Usage

The "src/client" contains Loiacono's client files, which are essential to build 
your client - let's call him EasyDriver. So you should create the "EasyDriver"
directory in the "src" folder and put your controller files (EasyDriver.h and 
EasyDriver.cpp" there). Basically, EasyDriver must inherit BaseDriver and 
implement the "drive" function (see the manual for simulation I/O details). After
that, just run "make DRIVER=EasyRider" and you'll get your client executable for
TORCS simulations.

If you're new to this, don't forget to look at Loiacono's SimpleDriver (in the 
"client" folder) for a "simple" implementation to get you started.

* Observations

Running TORCS in text-mode. XML file must be absolute path.