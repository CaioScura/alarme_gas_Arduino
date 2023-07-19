#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define GAS A5
#define ALARME 7

#define LG 8
#define LY 9
#define LR 10

byte caveira[8]={
 B00000,
 B01110,
 B10001,
 B11011,
 B10101,
 B11011,
 B01110,
 B00000,
};

int vr;

int pos = 14;

void alarme(){
  
   lcd.setCursor(14, 1);
  
  if (vr > 600){
    tone(ALARME, 600);
    lcd.print("  ");
    lcd.setCursor(pos, 1);
    lcd.write(1);
    
    digitalWrite(LG, LOW);
    digitalWrite(LR, HIGH);
    digitalWrite(LY, LOW);
    
  }else if (vr > 400 && vr < 600){
    tone(ALARME,300);
    lcd.print("AL");
    
    digitalWrite(LG, LOW);
    digitalWrite(LR, LOW);
    digitalWrite(LY, HIGH);
    
    
  }
  else{
    noTone(ALARME);
    lcd.print("OK");
    
    digitalWrite(LG, HIGH);
    digitalWrite(LR, LOW);
    digitalWrite(LY, LOW);
  }
  
}

void setup() {
  lcd.createChar(1, caveira);
  
  pinMode(GAS, INPUT);
  pinMode(ALARME, OUTPUT);
  
  pinMode(LY, OUTPUT);
  pinMode(LG, OUTPUT);
  pinMode(LR, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("ALARME - GAS");
}

void loop() {
  vr = analogRead(GAS);
  alarme();
  
  lcd.setCursor(0, 1);
  lcd.print("VR:");
  lcd.print(vr);
  
  delay(1000);
}