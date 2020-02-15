#include <dht.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
dht DHT;
#define DHT11_PIN 7

const int moistureAO=0;
int AO=0;
int tmp=0; 
//int LED=13;
int WATERPUMP = 13;
void setup() {
  mySerial.begin(9600);
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Soil Moisture");
  pinMode(moistureAO,INPUT);
  //pinMode(LED, OUTPUT);
   pinMode(WATERPUMP,OUTPUT);
   delay(100);
}

void loop() {
  Start:
  // put your main code here, to run repeatedly:
  tmp=analogRead( moistureAO);
  if ( tmp!= AO ){
    AO=tmp;
    Serial.println("  ");
    Serial.print("Soil Moisture A = ");
    Serial.println(AO);
  int chk = DHT.read11(DHT11_PIN);
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    Serial.print("Humidity = ");
    Serial.println(DHT.humidity);
  }
 delay(1000);
  if(AO>300){
    //Serial.println("LED High");
    //digitalWrite(LED,HIGH);
    digitalWrite(WATERPUMP,250);
    delay(5000);
    //digitalWrite(LED,LOW);
    //Serial.println("LED Low");
    digitalWrite(WATERPUMP,0);

    if (Serial.available()>0)
 {
      SendMessage();
 }  
 

 if (mySerial.available()>0)
 {
   Serial.write(mySerial.read());
}
  }
  else{
   // digitalWrite(LED,LOW);
  }

 
    goto Start;
    delay(1000);
     
}  



void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918866997039\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
