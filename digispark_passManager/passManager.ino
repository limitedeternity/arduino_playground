#include "DigiKeyboard.h"
#include <SoftSerial.h>
#include <TinyPinChange.h>

SoftSerial mySerial(2, 3); // RX, TX

char softCommand = '';
char hardCommand = '';

void setup() {
  Serial.begin(57600);
  
  while (!Serial) {
    ;
  }

  Serial.println("Hardware serial is up.");

  mySerial.begin(4800);
  mySerial.println("Software serial is up.");

  DigiKeyboard.update();
  
}


void loop() {
  if (mySerial.available() > 0) {
      DigiKeyboard.delay(100);
      DigiKeyboard.update();
      DigiKeyboard.delay(100);
      
      softCommand = mySerial.read();
      DigiKeyboard.sendKeyStroke(0);

      if (softCommand == '<service>') {
          Serial.println("Writing password in...");
          
          for (int i = 5; i > 0; i--) {
              Serial.write(i);
              Serial.write("...");
              delay(1000);
          }
          
          DigiKeyboard.println("passwd");
          Serial.println("Password sent");
      } else {
          Serial.println("Invalid command");
      }
      
      DigiKeyboard.delay(100);
  }
  
  if (Serial.available() > 0) {
      DigiKeyboard.delay(100);
      DigiKeyboard.update();
      DigiKeyboard.delay(100);

      hardCommand = Serial.read();
      DigiKeyboard.sendKeyStroke(0);

      if (command == '<service>') {
          mySerial.println("Writing password in...");
          
          for (int i = 5; i > 0; i--) {
              mySerial.write(i);
              mySerial.write("...");
              delay(1000);
          }
          
          DigiKeyboard.println("passwd");
          mySerial.println("Password sent");
      } else {
          mySerial.println("Invalid command");
      }

      DigiKeyboard.delay(100);
  }
  
  delay(1000);
}
