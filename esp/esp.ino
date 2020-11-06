/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - ESP8266 board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial
#define DHTTYPE DHT22

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "keys.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char *auth = auth_secret;

// Your WiFi credentials.
// Set password to "" for open networks.
char *ssid = ssid_secret;
char *pass = pass_secret;

const int DHTPin = 5;

const static int VPIN_TEMP = 6;
const static int VPIN_HUMID = 7;

BlynkTimer timer;
DHT dht(DHTPin,DHTTYPE);

const static long FIFTEEN_MINUTES = 900000; //milliseconds

void setup()
{
//  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(FIFTEEN_MINUTES, updateDHT);
}


void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}



void updateDHT() {
  float newT = dht.readTemperature();
  float newH = dht.readHumidity();
//  Serial.print(newT);
//  Serial.print(newH);
  if (!isnan(newT)) {
    Blynk.virtualWrite(VPIN_TEMP, newT);
  }
  if (!isnan(newH)) {
    Blynk.virtualWrite(VPIN_HUMID, newH);
  }

}
