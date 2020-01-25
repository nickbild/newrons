#include "secret.h"
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>

#define INLEN 256
char instr[INLEN + 1];

Adafruit_NeoPixel pixels(1, 6, NEO_GRB + NEO_KHZ800);

RTC_PCF8523 rtc;

void setup() {
  // USB.
  Serial.begin(115200);
  
  // JeVois device.
  Serial1.begin(115200);
  Serial1.setTimeout(500);

  // 5050 LED
  pinMode(6, OUTPUT);
  pixels.begin();

  // Flash LED to indicate device is on.
  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();

  // PCF8523 real-time clock.
  rtc.begin();

  // Get current date/time.
  DateTime now = rtc.now();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // Run once to initialize clock.

//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.print(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.print(" ");
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.print(now.second(), DEC);
//  Serial.println();
  
  // Get Google calendar events.
  String apiUrl = "https://www.googleapis.com/calendar/v3/calendars/" EMAIL_ADDRESS "/events?access_token=" ACCESS_TOKEN "&timeMin=2019-01-01T10:00:00-05:00&timeMax=2019-01-20T10:00:00-05:00";

}

void loop() {  
   // Read a line of data from JeVois:
   byte len = Serial1.readBytesUntil('\n', instr, INLEN);
 
   // Make sure the string is null-terminated:
   instr[len--] = '\0';
   
   // Cleanup any trailing whitespace:
   while (len >= 0 && instr[len] == ' ' || instr[len] == '\r' || instr[len] == '\n') instr[len--] = '\0';

   if (String(instr).startsWith("DO ")) {
    Serial.println(instr);
    
    if (String(instr).indexOf("pill_bottle") > -1) {
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
      pixels.show();
    } else if (String(instr).indexOf("microwave") > -1) {
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      pixels.show();
    } else if (String(instr).indexOf("running_shoe") > -1 || String(instr).indexOf("loafer") > -1) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 150));
      pixels.show();
    }
    
   }

}
