#define INLEN 256
char instr[INLEN + 1];
 
void setup() {
  // USB.
  Serial.begin(115200);
  
  // JeVois device.
  Serial1.begin(115200);
  Serial1.setTimeout(500);
}

void loop() {
   // Read a line of data from JeVois:
   byte len = Serial1.readBytesUntil('\n', instr, INLEN);
 
   // Make sure the string is null-terminated:
   instr[len--] = '\0';
   
   // Cleanup any trailing whitespace:
   while (len >= 0 && instr[len] == ' ' || instr[len] == '\r' || instr[len] == '\n') instr[len--] = '\0';

   if (strcmp(instr, "") != 0) {
    Serial.println(instr);
   }

}
