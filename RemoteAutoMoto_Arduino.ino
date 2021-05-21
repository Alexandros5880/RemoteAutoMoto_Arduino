#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial hc06(2,3);

// Bluetooth module
int power_button = A3;
int start_button = A4;
int stop_button = A5;
String text;
char c;

// Excecute function
void excecuteOrder();

// Keypad
#include <Keypad.h>
const byte ROWS2 = 4; //four rows
const byte COLS2 = 4; //four columns
char keys2[ROWS2][COLS2] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins2[ROWS2] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {8, 7, 6, 5}; //connect to the column pinouts of the keypad
Keypad keypad2 = Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2 );

// Read Keypad Function
void getKyepad();

// Keyboard variables
String data1 = "";
String data2 = "";
char key1 = "";
char key2 = "";

// Passwords
String password_A = "1234A";
String password_B = "1234B";
String password_C = "1234C";
String password_D = "1234D";


void setup() {
  Serial.begin(9600);
  //Initialize Bluetooth Serial Port
  hc06.begin(9600);
  pinMode(power_button, OUTPUT);
  pinMode(start_button, OUTPUT);
  pinMode(stop_button, OUTPUT);
  delay(7);
  Serial.println();
}

void loop() {

  // Read Keypad
  getKyepad();

  // Excecute bluetooth orders
  excecuteOrder();

  delay(100);
}




// Read Keypad Function
void getKyepad() {
  key1 = keypad2.getKey();
  if (key1 != key2) {
    key2 = key1;

    if (key1) {
      data1 += key1;
    }

    if (key1 == 'A' || key1 == 'B' || key1 == 'C' || key1 == 'D' || key1 == '*') {
      switch (key1) {
        case 'A': 
              if ( data1 == password_A ) {
                Serial.println("Power ON");
                digitalWrite(power_button, HIGH);
              }
              data1 = "";
              break;
        case 'B':
              if ( data1 == password_B ) {
                Serial.println("Power ON");
                digitalWrite(power_button, HIGH);
              }
              data1 = "";
              break;
        case 'C': 
              if ( data1 == password_C ) {
                Serial.println("Power ON");
                digitalWrite(power_button, HIGH);
              }
              data1 = "";
              break;
        case 'D': 
              if ( data1 == password_D ) {
                Serial.println("Power ON");
                digitalWrite(power_button, HIGH);
              }
              data1 = "";
              break;
        case '*': 
              data1 = "";
              Serial.println("Power OFF");
              digitalWrite(power_button, LOW);
              break;
        case '#':
              Serial.println("#");
              break;
      }
    }
    
  }
}


// Excecute Order Function
void excecuteOrder() {

  // Read Bluetooth
  while (hc06.available()) {
    c = hc06.read();
    if (c != NULL) {
      text += c;
      delay(7);
    }
  }
  
  // Power ON
  if (text == "on_power") {
    Serial.println("Power ON");
    digitalWrite(power_button, HIGH);
  }
  // Power OFF
  if (text == "off_power") {
    Serial.println("Power OFF");
    digitalWrite(power_button, LOW);
  }
  // Engine ON
  if (text == "on_engine") {
    Serial.println("START");
    digitalWrite(start_button, HIGH);
    delay(1500);
    digitalWrite(start_button, LOW);
  }
  // Stop Engine Button ON
  if (text == "Stop") {
    Serial.println("Stop Engine ON");
    digitalWrite(stop_button, HIGH);
  }
  // Stop Engine Button OFF
  if (text == "Stop_off") {
    Serial.println("Stop Engine OFF");
    digitalWrite(stop_button, LOW);
  }
  text = "";
}