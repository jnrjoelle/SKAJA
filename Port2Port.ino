#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 4); // RX, TX

String myaddress = "A11";
String token = '';

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() { // run over and over
  if (token.equals('')) {//token empty fill token
    if (Serial.available() > 0) {
      token = Serial.read();
      mySerial.write(token);
    }
  }
  else {
    int begdest = token.indexOf("-");
    int enddest = token.indexOf("/");//seperates the destination from the rest of the string
    if (token.substring(begdest + 1, enddest).equals(myaddress)) {//if my address is the one being sent to accept message
      if (mySerial.available() > 0) {
        Serial.write(mySerial.read());
      }
    } else {//if it is not my address
      mySerial.write(token);//pass token along
    }
  }
}
