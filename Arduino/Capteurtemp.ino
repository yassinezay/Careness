int temp;
float grad;
char data;

#define ventipin 5

void setup() {
  pinMode(12, OUTPUT); // met la broche numérique en sortie
  pinMode(10, OUTPUT); // met la broche numérique en sortie
  pinMode(A1, INPUT);
  pinMode (8, OUTPUT);
  pinMode (ventipin, OUTPUT);
  Serial.begin(9600);  // ouvre le port série
  
}

void loop() {
  temp = analogRead(A1);
  grad = (temp/1023.0)*5.0*1000/10;
  Serial.println(grad);

  if (grad > 30) { digitalWrite(12, HIGH); digitalWrite(10, LOW);digitalWrite (8, HIGH); analogWrite(ventipin,255); }
  delay(500);
  if (grad < 30) { digitalWrite(12, LOW); digitalWrite(10, HIGH);  digitalWrite (8, LOW); analogWrite(ventipin,0) ;}
  delay(500);
 // attend 



 
  if (Serial.available()){     

     data=Serial.read();  
     if(data=='1') 
    {
     digitalWrite(12, HIGH); digitalWrite(10, LOW);digitalWrite (8, HIGH); analogWrite(ventipin,255);
     }  delay(500);
     if(data=='2') 

     {
      digitalWrite(12, LOW); digitalWrite(10, HIGH);  digitalWrite (8, LOW); analogWrite(ventipin,0);
     
     }   delay(500);
   
    
  }
     }
