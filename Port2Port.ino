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
    if (token.substring(endsrc + 1, enddest).equals(myaddress)) {//if my address is the destination 
      Serial.write(mySerial.read());
      received();
    } else if (token.substring(token.indexOf("$")+1,token.indexOf(endsrc)) {//if my address is the source
      Serial.write("Error");
    } else {//if it is not my address
      mySerial.write(&token);//pass token along
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
  
  String src = parsed.substring(0,parsed.indexOf("/"));
  String dest = src;
  src = myaddress;

  if(mySerial.available() > 0){
    token = "$"+src+"/"+dest+"-"+(string)sum+"_";
    mySerial.write(&token);
  }

}


