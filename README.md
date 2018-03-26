#Esper Module

Esper Module is extension of [Esper] framework for ESP8266 and ESP32 microcontrollers family.

The beauty of module implementation is abstraction from hardware layer.
You don’t need to upload your code to microcontroller and wait 30-50 seconds.
Instead you run code on local PC and mock hardware function calls.

In most of cases code logic don’t need real hardware behind.
You cover with unit test expected values on input and output pins and reaction to incoming Esper string commands.
When you are happy with logic, switch to hardware environment.
If hardware run shows in console correct behavior, then you ready to include module in to your Esper application.
If your module covers all the functionality you need then you can just use example Esper application.

File platformio.ini has configurations to run on local PC and to run on ESP8266.

#License

MIT


[//]: #

[Esper]: https://github.com/palivoda/esper
