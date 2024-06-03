#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#define laser 2
#define SS_PIN 10
#define RST_PIN 9
#define LED_GREEN 7
#define LED_RED 8
#define sensor 3
#define buzzer 6

int h=1;
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
 Serial.begin(9600);
  SPI.begin();
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
   pinMode(sensor, INPUT);
   pinMode(buzzer,OUTPUT); //Buzzer Pin
  mfrc522.PCD_Init();
  Serial.println("CARENESS RFID");
  pinMode(laser, OUTPUT);//lazer

  delay(500);
 
}

void loop() {
 char data;
int j=1;
   if (h==0){
       int i=0;
  if(digitalRead(sensor)==LOW)
{
   a:
  digitalWrite(LED_RED,HIGH);
  digitalWrite(buzzer,HIGH);
  digitalWrite(LED_GREEN,LOW);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
  j++;
  if(j==2)
  {
  Serial.write("3");
  }      
  i++;
  if(i<2){
  goto a;
  }else
  {
    digitalWrite(LED_RED,LOW);
    delay(100);}
  
  
  }
   }
   
 if (Serial.available()){     
    //Si un message a été reçu  faire ceci
     data=Serial.read(); 
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     delay(100);
     if(data == '1') //si le caractère lu est égale à 1
    {
      digitalWrite(laser,HIGH); // alumer la lampe 
      h=0;
  
     }  
     else if(data=='0') //si le caractère lu est égale à 0

     {
        digitalWrite(laser,LOW); //éteindre la lampe
        digitalWrite(buzzer,LOW);

        h=1;
    
     }}   
  
 if (!mfrc522.PICC_IsNewCardPresent() && data=='1') {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(laser, HIGH);
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    return;
  }

  String content = "";
    byte letter;
    char data1;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println(content);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  Serial.println("Emprunt détecté !");
     digitalWrite(laser, LOW);
     h=1;
     delay(2000);
  digitalWrite(LED_GREEN, LOW);
  delay(1000);

}
