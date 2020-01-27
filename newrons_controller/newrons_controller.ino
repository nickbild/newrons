#include "secret.h"
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>

#define INLEN 256
char instr[INLEN + 1];

Adafruit_NeoPixel pixels(1, 6, NEO_GRB + NEO_KHZ800);
RTC_PCF8523 rtc;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;

WiFiClient client;
char server[] = "www.googleapis.com";
int startSaving = 0;
String apiResult;

StaticJsonDocument<8000> doc;
int jsonParsed = 0;

int takeMeds = 0;
int goWalk = 0;
int makeLunch = 0;

void setup() {
  // USB.
  Serial.begin(115200);

  // JeVois device.
  Serial1.begin(115200);
  Serial1.setTimeout(500);

  // PCF8523 real-time clock.
  rtc.begin();

  // Get current date/time.
  DateTime now = rtc.now();
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // Run once to initialize clock.

  // Connect to WiFi.
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    
    // Wait 10 seconds for connection.
    delay(10000);
  }
  Serial.println("Connected to network.");

  // Get Google calendar events.
  DateTime minDT (now - TimeSpan(0, 1, 0, 0));
  String minTime = String(minDT.year()) + "-" + String(minDT.month()) + "-" + String(minDT.day()) + "T" + String(minDT.hour()) + ":" + String(minDT.minute()) + ":" + String(minDT.second()) + "-05:00";
  DateTime maxDT (now + TimeSpan(0, 1, 0, 0));
  String maxTime = String(maxDT.year()) + "-" + String(maxDT.month()) + "-" + String(maxDT.day()) + "T" + String(maxDT.hour()) + ":" + String(maxDT.minute()) + ":" + String(maxDT.second()) + "-05:00";
  
  String apiUrl = "/calendar/v3/calendars/" EMAIL_ADDRESS "/events?access_token=" ACCESS_TOKEN "&timeMin=" + minTime + "&timeMax=" + maxTime;

  if (client.connectSSL(server, 443)) {
    Serial.println("Connected to server.");
    client.println("GET " + apiUrl + " HTTP/1.1");
    client.println("Host: www.googleapis.com");
    client.println("Connection: close");
    client.println();
  }

  // 5050 LED
  pinMode(6, OUTPUT);
  pixels.begin();

  flashLED();
}

void loop() {
  while (client.available()) {
    char c = client.read();
    if (c == '{') {
      startSaving = 1;
    }

    if (startSaving) {
      apiResult += c;
    }
  }

  // Parse JSON.
  if (jsonParsed == 0 && apiResult != "") {
    DeserializationError error = deserializeJson(doc, apiResult);
  
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
    }
    
    jsonParsed = 1;
  }

  if (jsonParsed == 1) {
    JsonArray items = doc["items"];
    for (int i=0; i<items.size(); i++) {
      const char* summary = items[i]["summary"];
      Serial.println(summary);

      if (String(summary).indexOf("Take Medicine") > -1) {
        takeMeds = 1;
      } else if (String(summary).indexOf("Go for a walk")) {
        goWalk = 1;
      } else if (String(summary).indexOf("Make Lunch")) {
        makeLunch = 1;
      }

    }

    jsonParsed = 2;
  }
  
  // Read a line of data from JeVois:
  byte len = Serial1.readBytesUntil('\n', instr, INLEN);

  // Make sure the string is null-terminated:
  instr[len--] = '\0';

  // Cleanup any trailing whitespace:
  while (len >= 0 && instr[len] == ' ' || instr[len] == '\r' || instr[len] == '\n') instr[len--] = '\0';

  if (String(instr).startsWith("DO ")) {
    Serial.println(instr);

    if (String(instr).indexOf("pill_bottle") > -1 && takeMeds) {
      flashLED();
    } else if (String(instr).indexOf("microwave") > -1 && makeLunch) {
      flashLED();
    } else if ((String(instr).indexOf("running_shoe") > -1 || String(instr).indexOf("Loafer") > -1) && goWalk) {
      flashLED();
    }

  }

}

void flashLED() {
  for (int i=1; i<151; i++) {
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    pixels.show();
    delay(12);
  }
  
  for (int i=149; i>=0; i--) {
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    pixels.show();
    delay(12);
  }
}
