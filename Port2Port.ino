#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 4); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() { // run over and over
  if (mySerial.available()>0) { //gets # of bytes available for reasing from serial connection
    Serial.write(mySerial.read()); //read serial connection and output data to your Serial Monitor
  }
  if (Serial.available()>0) {
    mySerial.write(Serial.read());
  }
}
