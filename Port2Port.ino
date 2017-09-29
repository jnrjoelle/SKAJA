#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 4); // RX, TX

String myaddress = "A11";
String token = "$";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() { // run over and over
  if (token.equals("$")) {//token empty fill token
    if (Serial.available() > 0) {
      token = token + myaddress + "/" + Serial.read() + "_";
      mySerial.write(&token);
    }
  }
  else {//if token is filled with information check for data
    int begdest = token.indexOf("/");
    int enddest = token.indexOf("-");//separates the destination from the rest of the string
    if (token.substring(begdest + 1, enddest).equals(myaddress)) {//if my address is the one being sent to accept message
      if (mySerial.available() > 0) {
        Serial.write(mySerial.read());
        received();
      }
    } else {//if it is not my address
      mySerial.write(&token);//pass token along
    }
    if (token.substring(begdest + 1, enddest).equals("A11")) {
      Serial.write("Error");
    }
  }
}

void received(){
  int sum=0;
  String parsed = mySerial.read(); 
  String parsed2;  
  for(int i=0; i<parsed.length; i++){
    parsed2 = substring(i,i+1);
    sum+=parsed2.toInt();
  }

  if(mySerial.available() > 0){
    mySerial.write(sum + "destination");
  }

}


