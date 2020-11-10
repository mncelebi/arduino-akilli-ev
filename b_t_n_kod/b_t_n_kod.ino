#include <dht11.h>
#include <LiquidCrystal.h>
#include<Servo.h>
Servo nesne;
LiquidCrystal lcd(12,11,5,4,3,2);
dht11 DHT11;

#define led 9
#define led1 10
#define MotorPin A3
#define ses A1
#define hrkt 6

const int trigger_pin= 1;
const int echo_pin = 8;

int MotorDurum = LOW;
int sonuc;
int esikDegeri = 400;
int deger;
int zaman,uzaklik;  
String readString = "";

void setup() {
  pinMode(led,OUTPUT); 
  pinMode(led1, OUTPUT);
  pinMode(ses,OUTPUT);
  pinMode(MotorPin, OUTPUT);
  pinMode(trigger_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  
  digitalWrite(led1, LOW);
  Serial.begin(9600);

  lcd.begin(16,2);
  DHT11.attach(7);
  nesne.attach(13);
  

}

void loop() {
  //----------------------------------------------LDR İLE LED
  int isik = analogRead(A0); 
  Serial.println(isik);
  delay(50);

  if(isik > 900){ //Okunan ışık değeri 900'den büyük ise
    digitalWrite(led,LOW); //LED yanmasın
  }

    if(isik <= 900){ //Okunan ışık değeri 900'den büyük ise
    digitalWrite(led,HIGH); //LED yanmasın
  }
  //----------------------------------------------SES İLE LED
  while (Serial.available()) { 
 char c = (char)Serial.read();
 readString += c;
 }
 if (readString.length() > 0) { 
 if (readString == "led yak") { 
 digitalWrite(led1, HIGH);
 }
 if (readString == "led kapat") {
 digitalWrite(led1, LOW);
 }
 readString = ""; 
 }
 delay(100);
 //----------------------------------------------DC MOTOR

 while (Serial.available()) { 
 char c = (char)Serial.read();
 readString += c;
 }
if (readString.length() > 0) { 
 if (readString == "fan aç") {
 MotorDurum = HIGH;
 }
 if (readString == "fan kapat") {
 MotorDurum = LOW;
 }
 readString = "";
}
  delay(100);
  
//----------------------------------------------PIR

if(sonuc==1){
    digitalWrite(led,HIGH);
    digitalWrite(ses,HIGH);
    }
  else{
      digitalWrite(led,LOW);
      digitalWrite(ses,LOW);
      }
  Serial.println(sonuc);
  delay(100);

//----------------------------------------------GAZ KAÇAK

deger = analogRead(A2);           
  if(deger > esikDegeri){           
    digitalWrite(ses, HIGH);
    delay(100);
    digitalWrite(ses, LOW);
    delay(100);
  }
  else{                            
    digitalWrite(ses, LOW);
  }
//----------------------------------------------SERVO

  digitalWrite(trigger_pin,HIGH);
  delay(1000);
  digitalWrite(echo_pin,LOW);
  zaman = pulseIn(echo_pin,HIGH);
  uzaklik=(zaman / 2)/29.1;
  if(uzaklik <=4){
    nesne.write(90);
    delay(1000);
    }
   else
    {nesne.write(90);}

//----------------------------------------------TERMOMETRE

 lcd.setCursor(0,0);
 int chk = DHT11.read();
 lcd.print("Nem (%)"    );
 lcd.println((float) DHT11.humidity,DEC);
 lcd.setCursor(0,1);
 lcd.println((float)DHT11.temperature,DEC);
 delay(2000);
 
}
