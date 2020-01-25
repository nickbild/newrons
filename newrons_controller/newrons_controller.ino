#include <Adafruit_NeoPixel.h>

#define INLEN 256
char instr[INLEN + 1];

Adafruit_NeoPixel pixels(1, 6, NEO_GRB + NEO_KHZ800);
 
void setup() {
  // USB.
  Serial.begin(115200);
  
  // JeVois device.
  Serial1.begin(115200);
  Serial1.setTimeout(500);

  // 5050 LED
  pinMode(6, OUTPUT);
  pixels.begin();

  // Test LED.
  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
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
