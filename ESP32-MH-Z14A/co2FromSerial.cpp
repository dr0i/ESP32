/* Notes:
 *  The purpose of this program is to demonstrate the usage of the MH-Z14A on your
 *  ESP32 in the most primitive way, i.e. one file.
 *  The program is taken from https://github.com/rafalmag/ESP32-MH-Z14A made
 *  dumb stupid (no need of a library, everything at one page). Only the digital
 *  kind of sensor output is used, to be read by ESP32 UART, serial (They are called 
 *  RX and TX resp. GPIO 16 and GPIO 17 and in the middle of the right side of the 
 *  ESP32 (don't confuse them with RX2 and TX2 and the end of the ESP32)).
 *  
 *  Look at http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z14a_co2-manual-v1_01.pdf
 *  and connect your ESP32 with the MH-Z14A (Pad n):
 *  
 *   5v DC -------> Pad 17
 *   Ground ------> Pad 16
 *   TX ----------> Pad 18
 *   RX ----------> Pad 19
 *  
 *  (See also https://www.hackster.io/kritch83/getting-started-with-the-mh-z14a-co2-detector-e96234#team)
 *  
 *  Keep in mind to power the MH-Z14A with 5V, not with the 3.3V, or you get
 *  either 410 or 430 ppm or, with the sensor rebooting, 5000 ppm (and error -1).
 *  The ESP32 provides both, 3.3V and 5V output. The latter is named "VIN" on the
 *  board. See https://www.esp32.com/viewtopic.php?t=11904.
 *  
 *  Further: direct sunlight influences the sensor because it measures infrared.
 *  Also a windy place may be problematic.
 *  
 * Thanks to https://www.letscontrolit.com/forum/viewtopic.php?t=1785 I got the
 * problems solved.
 * 
 * If you use arduino ide make sure to set the "Serial Monitor" to 9600 baud to
 * view the output.
 * 
 * If you uncomment "calibrate the sensor" the sensor will be calibrated every time
 * you start the program. Don't calibrate your CO2-Sensor too often, it could break.
 * Less than ones per minute should be safe.
 * 
 * Again, this program is not a good example of how to do it! You would separate
 * the C++ header files from instantiating code and data. See @rafalmag's repo where
 * this is done properly.
 */

/**
   simple MH-Z14A CO2 level monitor
   ESP32 
   Based on : https://github.com/coniferconifer/co2sensor
   License: Apache License v2
*/

#include <Arduino.h>

int baudRate = 9600;
class Co2FromSerial
{
private:
  HardwareSerial serial;
  static const uint8_t readCo2Cmd[];
  void clearSerialBuffer();

public:
  Co2FromSerial(HardwareSerial serial);
  void init();
  int getCO2();
};


const uint8_t Co2FromSerial::readCo2Cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

Co2FromSerial::Co2FromSerial(HardwareSerial serial) : serial(serial)
{
}

void Co2FromSerial::init()
{
    serial.begin(baudRate);  // communication for MH-Z14A
    clearSerialBuffer(); // read out garbage (i have no idea why but this is a must have for mobile battery operation)
}

void Co2FromSerial::clearSerialBuffer()
{
    uint8_t c;
    while (serial.available())
    {
        c = serial.read();
    }
}

int Co2FromSerial::getCO2()
{
    int returnnum = 0;
    uint16_t co2 = 0;
    uint8_t readBuffer[9] = {};
    int i;
    uint8_t checksum = 0;
    clearSerialBuffer();

    serial.write(readCo2Cmd, sizeof(readCo2Cmd));
    serial.setTimeout(300); //set 300msec timeout
    returnnum = serial.readBytes(readBuffer, sizeof(readBuffer));

    if ((readBuffer[0] == 0xFF) && (readBuffer[1] == 0x86))
    {
        for (i = 1; i < 8; i++)
        {
            checksum += readBuffer[i];
        }
        checksum = 0xff - checksum;
        checksum += 1;
        if (readBuffer[8] != checksum)
        {
            Serial.println("check sum error");
            return (-1); // -1 indicates check sum error
        }
        co2 = (uint16_t)readBuffer[2] << 8;
        co2 += readBuffer[3];
        return co2;
    }
    else
    {
        return -1;
    }
}

HardwareSerial serialCo2(2); // RX(green) to GPIO 16, TX(blue) to GPIO 17

Co2FromSerial co2FromSerial(serialCo2);

void setup()
{
  co2FromSerial.init();
  Serial.begin(baudRate);
}

boolean calibrated = false;
int measureFrequencySeconds = 5;
void loop()
{
  Serial.println(String("CO2 level(ppm):") + co2FromSerial.getCO2());
  
 /* uncomment to calibrate the sensor. Don't do it too often.
  if (!calibrated) {
    delay (4000);
    calibrate();
    calibrated = true;
  }*/
  
  delay(measureFrequencySeconds*1000);
}

void calibrate()
{
  byte cmdCal[9] = {0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78};  // calibrate command
  Serial.println(String("going to calibrate..."));
  Serial.write(cmdCal, 9);
  delay(9000);
}
