#include <SoftwareSerial.h>
SoftwareSerial  SIM900(7,8);

int REDLed = 2;
int GREENLed = 3;
int BLUELed = 4;
int RED2Led = 5;
int GREEN2Led = 6;
int BLUE2Led = 10;


void setup() {
  // put your setup code here, to run once:
pinMode(REDLed, OUTPUT);
pinMode(GREENLed, OUTPUT);
pinMode(BLUELed, OUTPUT);
pinMode(RED2Led, OUTPUT);
pinMode(GREEN2Led, OUTPUT);
pinMode(BLUE2Led, OUTPUT);

SIM900.begin(19200);
Serial.begin(19200);
Serial.print("Power Up");
delay(40000);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("SubmitHttpRequest- Started");
SubmitHttpRequest();
Serial.println("SubmitHttpRequest - finished");
delay(10000);

}

void SubmitHttpRequest()
{
  
  SIM900.println("AT+CSQ");  // this is to check signal quality
  delay(100);
  ShowSerialData();
  ShowSerialData();
  
  SIM900.println("AT+CGATT?");
  delay(100);
  ShowSerialData();
  
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");
  delay(4000);
  ShowSerialData();
  SIM900.println("AT+SAPBR=1,1");
  delay(2000);
  ShowSerialData();
  SIM900.println("AT+HTTPINIT");
  delay(2000);
  ShowSerialData();
  
  SIM900.println("AT+HTTPPARA=\"URL\",\"http://campusshop.com.ng/homeautomation/web/api/v1/device/devicestate/1\"");
 
  delay(1000);
  ShowSerialData();
  SIM900.println("AT+HTTPACTION=0");
  delay(10000);
  ShowSerialData();
  SIM900.println("AT+HTTPREAD");
  delay(3000);

  ChangeLed();
  ShowSerialData();
  SIM900.println("*");
  delay(100);
  
  
}

void ChangeLed()
{
 
 String content = "";
while(SIM900.available()!=0){
 Serial.println("**");
 content = content + String(char(SIM900.read()));
} 
Serial.println(content);
Serial.println(content.substring(60,61));
if(content.substring(55,56) == "0"){
  digitalWrite(REDLed,LOW); // Turns ON Relays 1


}
else if(content.substring(55,56) == "1"){
 digitalWrite(REDLed, HIGH);
}

if(content.substring(56,57) == "0"){
  digitalWrite(GREENLed,LOW); // Turns ON Relays 1


}
else if(content.substring(56,57) == "1"){
 digitalWrite(GREENLed, HIGH);
}

if(content.substring(57,58) == "0"){
  digitalWrite(BLUELed,LOW); // Turns ON Relays 1


}
else if(content.substring(57,58) == "1"){
 digitalWrite(BLUELed, HIGH);
}


if(content.substring(58,59) == "0"){
  digitalWrite(RED2Led,LOW); // Turns ON Relays 1


}
else if(content.substring(58,59) == "1"){
 digitalWrite(RED2Led, HIGH);
}


if(content.substring(59,60) == "0"){
  digitalWrite(GREEN2Led,LOW); // Turns ON Relays 1


}
else if(content.substring(59,60) == "1"){
 digitalWrite(GREEN2Led, HIGH);
}


if(content.substring(60,61) == "0"){
  digitalWrite(BLUE2Led,LOW); // Turns ON Relays 1


}
else if(content.substring(60,61) == "1"){
 digitalWrite(BLUE2Led, HIGH);
}

}

void ShowSerialData()
{
 while(SIM900.available()!=0){
  Serial.write(char(SIM900.read()));
 } 
}
