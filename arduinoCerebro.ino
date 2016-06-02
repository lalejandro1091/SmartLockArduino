#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Keypad.h>
#include <ctype.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//LiquidCrystal lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char * code="memepute";
char * coderas="meempute";
int cont = 0;
String codera = "";
int i = 0;
int led = 13;
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("Adafruit finger detect test");
  /*lcd.begin(20, 4);
  for(i = 0; i < 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();*/
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}
void loop()
{
    if(getFingerprintIDez() != -1){
      Serial.println("se abre la puerta");
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
    }/*else if(Serial.available()>0){
    if(Serial.available()>0){
      //array de lectura por string
      codera = Serial.readString();
    }
    for(i = 0; i < 6; i++){
    coderas[i] = codera[i];
    }
    i = 0;
    //lcd.write("Recibiendo: ");
    while(i < 6){
    code[i] = keypad.getKey();
    //lcd.write(code[i]);
    i++;
    }
    i = 0;
    while(i < 6){
      if(code[i] == coderas[i]){
        cont = cont + 1;
      }
      i++;
    }
    //lcd.clear();
    if (cont >= 5){
      //lcd.write("se abre la puerta");
      digitalWrite(led, HIGH);
      delay(100);
      //lcd.clear();
    }else{
      //lcd.write("no abre la puerta");
      //digitalWrite(led, LOW);
      delay(100);
      //lcd.clear();
    }
    digitalWrite(led, LOW);
    code = " ";
    cont = 0;
}*/
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
