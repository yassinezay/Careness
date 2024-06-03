#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>
#include <Wire.h> 
#include <RtcDS1302.h>


//0x3F or 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);   //LCD Object
#define _DATE_ "2023-05-02"
#define _TIME_ "14:30:00"
ThreeWire myWire(8, 7, 9);        // DAT, CLK, RST
RtcDS1302<ThreeWire> Rtc(myWire);    // RTC Object


const int buzzerPin = 10; // Définition de la broche pour le buzzer
int a ;
int i=59;
String name;
void setup ()
{
  Serial.begin(9600);
    pinMode(buzzerPin, OUTPUT); // Configuration de la broche du buzzer en sortie
  lcd.init();
  
  lcd.backlight();
  lcd.clear();
  Rtc.Begin();

  RtcDateTime currentTime = RtcDateTime(_DATE_ , _TIME_);
  Rtc.SetDateTime(currentTime);


  delay(4000);
  
 RtcDateTime now = Rtc.GetDateTime();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(now.Day());
  lcd.print("/");
  lcd.print(now.Month());
  lcd.print("/");
  lcd.print(now.Year());

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(now.Hour());
  lcd.print(":");
  lcd.print(now.Minute());
  lcd.print(":");
  lcd.print(now.Second());
  delay(10000);
  
}


void loop ()
{

    if (Serial.available()){
        lcd.clear();

  name=Serial.readString();
  lcd.print("Bonjour");
    lcd.setCursor(0, 1); // Positionnement du curseur en haut à gauche de l'écran LCD
    lcd.print(name);
    delay(5000);
  
  lcd.clear();
    lcd.setCursor(0, 0); // Positionnement du curseur en haut à gauche de l'écran LCD
  lcd.print("Focus Time :"); // Affichage du titre sur l'écran LCD
  lcd.setCursor(0, 1); // Positionnement du curseur sur la deuxième ligne
  lcd.print("Duration:"); // Affichage de l'étiquette "Durée" sur l'écran LCD
  do{
  for(a=1; a>0 ; a--){
      delay(800);
        lcd.setCursor(12, 1); // Positionnement du curseur sur la deuxième ligne
          lcd.print(a-1);
          
        lcd.print(":"); 

        for(i=10; i>=1 ; i--){
          delay(800);
        lcd.setCursor(14, 1); // Positionnement du curseur sur la deuxième ligne
          lcd.print(i); // Affichage du temps restant en minutes
        
        if (i < 10) { // Si les secondes sont inférieures à 10, ajouter un zéro devant
        lcd.setCursor(14,1);
            lcd.print("0");
            lcd.setCursor(15, 1); // Positionnement du curseur sur la deuxième ligne
          lcd.print(i);
          }
    

          
        }
}

}while((a-1) == 0);

 lcd.clear();
 lcd.print("Time for a pause");
delay(500);
    tone(buzzerPin, 262);
    delay(500);
        tone(buzzerPin, 555);
delay(500);
    }
}
