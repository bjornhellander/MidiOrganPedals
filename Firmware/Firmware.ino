/* Simple "Hello World" example.

   After uploading this to your board, use Serial Monitor
   to view the message.  When Serial is selected from the
   Tools > USB Type menu, the correct serial port must be
   selected from the Tools > Serial Port AFTER Teensy is
   running this code.  Teensy only becomes a serial device
   while this code is running!  For non-Serial types,
   the Serial port is emulated, so no port needs to be
   selected.
*/

const int ledPin = 6; // Teensy++ 2.0 has the LED on pin 6
int count = 0;
int ledOn = 1;

void setup() {
  Serial.begin(9600); // USB is always 12 Mbit/sec
  pinMode(ledPin, OUTPUT);
}

void loop() {
  count++;
  char message[50];
  snprintf(message, sizeof(message), "Hello World (%d)", count);
  Serial.println(message);
  
  ledOn = !ledOn;
  digitalWrite(ledPin, ledOn);
  
  delay(1000);
}
