# ArduinoMec2
Arduino reader from buderus MEC2 controller

Inspired by <a href="https://holzleitner.com/el/buderus-monitor/index-en.html">Peter Holzleitner</a> and <a href="https://github.com/bellerofonte/buderus-monitor">bellerofonte</a> I created a project on Arduino Mega2560 reading data from the bus on buderus logamatic 4xxx system. Retrieved data can be saved, or further processed.
According to Peter's page, there is a documentation (in DE), which describes the protocol. Try serach for "Monitordaten_System_4000_V1_7747004149_01-2009.pdf".

Using the schematic for the opto-isolated level translator https://github.com/bellerofonte/buderus-monitor/raw/master/schematic.png you can connect to bus on logamatic (BF connector on logamatic, or somewhere between MEC2 and logamatic) with one end and other end will connect to +5V, Gnd and Serial3 RX on arduino mega.

This simple sketch reads from Serial3 on arduino Mega, parses some data and write them out on Serial line to PC.
Hope taht someonne can find this helpful. You can incorporate it to your solution. 

Use at your own risk.
