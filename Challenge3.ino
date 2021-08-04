#include <IRremote.h>
#define A 0xF
#define B 0xF
#define C 0xF
#define O 0xF
#define ON_OFF_KEY 0xF



const int RECV_PIN = 11;
const int redPin = 8;
const int greenPin = 9;
const int yellowPin = 10;
//const int piezo = 12;

int red = 0;  // Initial intensity
int green = 0;
int yellow = 0;
int currentBrightness = 0;  // Initial active color intensity
String targetColor = "RED"; // Initial active color
bool isOn = false;

IRrecv irrecv(RECV_PIN);  // Initialize IR Library
decode_results results;   // Initialize IR Library


void setup() {
  Serial.begin(9600);   // Start Serial
  irrecv.enableIRIn();  // Start the receiver
  // Set the three LED Pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
//  pinMode(piezo, OUTPUT);
}



void loop() {
  if (irrecv.decode(&results)) {
    // Serial.println(results.value, HEX);  // Prints HEX code IR receiver receives
    irrecv.resume(); // Receive the next value
    // Power switch
    if (results.value == ON_OFF_KEY) {
      if (isOn == true) {
        Serial.println("Turning Off"); powerOff();
      }
      else if (isOn == false) {
        Serial.println("Turning On"); powerOn(); 
        showCurrentActiveColor();
      }
    }
    
    // Color operations
    if (isOn == true) {
      if (results.value == A) {
        turnRed();
      }

      else if (results.value == B) {
        turnYellow(); 
      }

      else if (results.value == C) {
        turnGreen();
      }

//      else if (results.value == O) {
//        turnPiezo();
//      }
    }
  }
  delay(100);
}

void turnYellow() {
  digitalWrite(yellowPin, HIGH);
  delay(1000);
  digitalWrite(yellowPin, LOW);
  delay(500);
}

void turnGreen() {
  digitalWrite(greenPin, HIGH);
  delay(1000);
  digitalWrite(greenPin, LOW);
  delay(500);
}

void turnRed() {
  digitalWrite(redPin, HIGH);
  delay(1000);
  digitalWrite(redPin, LOW);
  delay(500);
}

//void turnPiezo() {
//  tone(piezo, 1000); // Send 1KHz sound signal...
//  delay(1000);        // ...for 1 sec
//  noTone(piezo);     // Stop sound...
//  delay(1000);        // ...for 1sec
//}






// Print current color setting on serial monitor
void showCurrentActiveColor() {
  Serial.print("Now controlling color ");
  Serial.println(targetColor);
}
// Turn Off LED
void powerOff() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(yellowPin, 0);
  isOn = false;
}

// Turn on LED
void powerOn() {
  updateColor();
  isOn = true;
}
// Turn up brightness for active color
//void brightnessUp() {
//  currentBrightness = (currentBrightness + 25) % 256;
//  updateColor();
//}
//// Turn down brightness for active color
//void brightnessDown() {
//  currentBrightness = max(0, (currentBrightness - 25) % 256);
//  updateColor();
//}

// Toggle active color that you are changing brightness on
//void toggleActiveColor() {
//  if (targetColor == "RED")
//    targetColor = "GREEN";
//  else if (targetColor == "GREEN")
//    targetColor = "yellow";
//  else if (targetColor == "yellow")
//    targetColor = "RED";
//  showCurrentActiveColor();
//}
// Update LED color to current setting
void updateColor() {
  if (targetColor == "RED")
    red = currentBrightness;
  else if (targetColor == "GREEN")
    green = currentBrightness;
  else if (targetColor == "yellow")
    yellow = currentBrightness;
  setColor(red, green, yellow);
  showColorOnSerialMonitor();
}
// Display current color in Serial Monitor
void showColorOnSerialMonitor() {
  Serial.print("Red ");
  Serial.print(red / 255.0);
  Serial.print("\tGreen ");
  Serial.print(green / 255.0);
  Serial.print("\tyellow ");
  Serial.println(yellow / 255.0);
}
// Output desired voltages to LED
void setColor(int red, int green, int yellow) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(yellowPin, yellow);
}
//// Circle through different colors
//void circle() {
//  red = 255;
//  green = 127;
//  yellow = 0;
//  Serial.println("Start Circle");
//  while (true) {
//    red = (red + 25 + 256) % 256;
//    green = (green + 25 + 256) % 256;
//    yellow = (yellow + 25 + 256) % 256;
//    setColor(red, green, yellow);
//    showColorOnSerialMonitor();
//    delay(150);
//    if (irrecv.decode(&results)) {
//      Serial.println("Stop Circle");
//      irrecv.resume();
//      return;
//    }
//  }
//}
