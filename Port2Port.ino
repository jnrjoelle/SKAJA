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
  if (mySerial.available() > 0) {
    token = mySerial.read();
  }
  if (token.equals("$")) {//token empty fill token
    if (Serial.available() > 0) {
      token = token + myaddress + "/" + Serial.read() + "_";
      mySerial.write(&token);
    }
  }
  else {//token full read
    int endsrc = token.indexOf("/");
    int enddest = token.indexOf("-");//separates the destination from the rest of the string
    String Message = token.substring(enddest + 1, token.indexOf("_"));//seperates the message from the token
    if (token.substring(endsrc + 1, enddest).equals(myaddress)) {//if my address is the destination
      Serial.print(Message);
      received(token);
      token = "$";
    } else if (token.substring(token.indexOf("$") + 1, token.indexOf(endsrc)).equals(myaddress)) { //if my address is the source
      Serial.write("Error");
    } else if (token.substring(endsrc + 1, enddest).equals("A0")) {
      if (token.substring(token.indexOf("$") + 1, token.indexOf(endsrc)).equals(myaddress)) {
        token = "$";
      } else {
        Serial.print(Message);
        received(token);
      }
    } else {//if it is not my address
      mySerial.write(&token);//pass token along
    }
  }
}

void received(String parsed) {
  int sum = 0;
  String parsed2;
  for (int i = 0; i < parsed.length(); i++) {
    parsed2 = parsed.substring(i, i + 1);
    sum += parsed2.toInt();
  }

  String src = parsed.substring(0, parsed.indexOf("/"));
  String dest = src;
  src = myaddress;

  if (mySerial.available() > 0) {
    token = "$" + src + "/" + dest + "-" + String(sum) + "_";
    mySerial.write(&token);
  }

}
