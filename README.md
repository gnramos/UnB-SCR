TORCS
=====
For lack of a better name, this project is currently called _TORCS_.

Description
-----------
An attempt to evolve TORCS controller(s).

Installation
------------
As per the "Simulated Car Racing Championship Competition Software Manual" ([v2 - April 2013](http://arxiv.org/pdf/1304.1672v2)), install TORCS 1.3.4.

Download this project's files anywhere you want them (say, "~/workspace"), the 
client works through UDP.

Usage
-----
The "src/client" contains Loiacono's client files, which are essential to build 
your client - let's call him _EasyDriver_. So you should create the "EasyDriver"
directory in the "src" folder and put your controller files (<code>EasyDriver.h</code> and 
<code>EasyDriver.cpp</code>" there). Basically, EasyDriver must inherit BaseDriver and 
implement the "drive" function (see the manual for simulation I/O details). After
that, just run "<code>make DRIVER=EasyRider</code>" and you'll get your client executable for
TORCS simulations.

If you're new to this, don't forget to look at Loiacono's SimpleDriver (in the 
"client" folder) for a "simple" implementation to get you started.

Observations
------------
To run TORCS in text-mode, the XML configuration file must be given with absolute path.