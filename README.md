# ESP32: how to

This is a repo explaining how to program the ESP32 and use some sensors like
e.g. the CO2-sensor MH-Z14A.

I am an absolute beginner when it comes to C++ or microcontroller or sensors.
I am a pro in doing things wrong at first - and by writing it down to
avoid that hopefully in the future.

So here is some of the wrongs I stumbled into:

## Connect ESP32 with cable to PC
Find the proper cable (on \*nix ):

```basic
10 $ ls /dev/tty* > unconnected.log; 
20 connect with a new cable
30 $ ls /dev/tty* > connected.log ; 
40 $ diff unconnected.log connected.log
50 if no tty shows up in the diff, goto 20
```

I had to try *6* cables before '/dev/ttyUSB' did show up - what a relieve, ESP32
not broken!

## IDE
Download the arduino ide from their homepage (not via your OS packet
manager - it may be way outdated!). 

Install esptools: https://github.com/espressif/esptool/

(on linux: $ pip3 install esptool. 
There is also a Debian/Ubuntu package python3-serial that can be installed first (apt install python3-serial)

Bring the ESP32 board to recognition by arduino ide:
Follow "Installation instructions using Arduino IDE Boards Manager" at
https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md:

File->Preferences->additional_boards_manager_urls: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

Then Tools->Board_menu and install esp32 platform (and don't forget to select
your ESP32 board from Tools->Board_menu after installation).

If you got "EMRDY:1" when in arduino ide->tools->serial_monitor you are not
connected. Wrong serial port or wrong cable or what.

If you upload a sketch and only get characters trash like:

)%M⸮

every second or so, press the small "en" button on your ESP32. This enables it.

## Use some sensors

### DHT22 humidity and temperature
See https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/

Read the DHT22 humidity and temperature sensor following. Worked instantly :)

### MH-Z14A CO2-Sensor
See https://github.com/rafalmag/ESP32-MH-Z14A

Read the MH-Z14A CO2-Sensor. That was hard - I got some plausible,
but very round measure (either 410 ppm or 430 ppm) around 12 times, after which I got
permanently 5000 ppm and sometimes -1 . 5000 ppm happens to be the  maximum of the sensors
measuring capacity. That's also the value written to output after the sensor is
booted. So ... problem was that I connected
the ESP32 eve 3.3V connector to power the MH-Z14A like proposed in "DHT22" (where
this was sufficient to use the DHT22) via the breadboard as shown in the link
above. After reading
https://www.letscontrolit.com/forum/viewtopic.php?f=2&t=1785 I understood
that the problem was too low voltage. Here 
https://www.esp32.com/viewtopic.php?t=11904 is shown how to get the 5V (it's
the red VIN connector). Now the sensor measures nice, unround values :)
