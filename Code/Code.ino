/*
  This code was written by Vrushit Patel on 2023-02-15
  Last updated 2023-02-15
*/

// Define the positions of the servo
#include <Servo.h>
int pos1 = 145; // Home (hinged lid is closed, hinding the finger)
int pos2 = 0; // Switch off position (hinged lid is open with finger touching the switch)
int pos3 = 40; // Back up, but not all the way home
int pos4 = 23; // Nealy touching the swtich

int i; // Used for slowing servo
int count = 0; // Used for cycling through the preset motion sequences
bool switchState = 0;

int switchPin = 10; // Define the pin for the toggle switch
int servoPin = 8; // Define the pin for the servo data
  
Servo myServo;

void setup(){
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(switchPin, INPUT);
  myServo.write(pos1);
  
  Serial.print("Switch count: ");
  Serial.println(count);
}

void loop(){
  switchState = digitalRead(switchPin);

  if(switchState == 0){
  count++;

    // Preset motion sequence #1
    if(count == 1)
    {
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 1: Slight Delay");
      
      delay(900);
      myServo.write(pos2);
      delay(400);
      myServo.write(pos1);
      switchState = 0;     
    }

    // Preset motion sequence #2
    if(count == 2 || count == 7 || count == 10)
    {
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 2: Normal Closing");

      delay(500);
      myServo.write(pos2);
      delay(400);
      myServo.write(pos1);
      switchState = 0;     
    }

    // Preset motion sequence #3
    else if(count == 3){
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 3: Delayed Closing");
      
      delay(2000);
      myServo.write(pos2);
      delay(400);
      myServo.write(pos1);
      switchState = 0;
    }

    // Preset motion sequence #4
    else if(count == 4 || count == 8){
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 4: Slow Motion");

      for(i = pos1; i >= pos3; i -= 1){
        // in steps of 1 degree
        myServo.write(i);
        delay(20);
      }
      delay(1000);
      myServo.write(pos2);
      delay(400);
      myServo.write(pos1);
      switchState = 0;
    }

    // Preset motion sequence #5
    else if(count == 5){
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 5: Teasing");
      
      delay(200);
      myServo.write(pos2);
      delay(400);
      myServo.write(pos3);
      delay(200);
      myServo.write(pos2);
      delay(200);
      myServo.write(pos3);
      delay(200);
      myServo.write(pos2);
      delay(200);
      myServo.write(pos3);
      delay(200);
      myServo.write(pos2);
      delay(200);
      myServo.write(pos3);
      delay(200);
      myServo.write(pos2);
      delay(200);
      myServo.write(pos3);
      delay(200);
      myServo.write(pos2);
      delay(2000);
      myServo.write(pos1);
      switchState = 0;
    }

    // Preset motion sequence #6
    else if(count == 6){
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 6: Opens But Not Touching Switch Goes to Scenerio 2 then");
      
      delay(200);
      myServo.write(pos3);
      delay(1500);
      myServo.write(pos1);
      switchState = 0;
    }

    // Preset motion sequence #7
    else if(count == 9){
      Serial.print("Switch count: ");
      Serial.print(count);
      Serial.println(" | Sceniario 7: Touch And Goes Comes Back to Close it");

      myServo.write(pos4);
      delay(2500);
      for(i = pos4; i <= pos1; i += 1){
        // in steps of 1 degree
        myServo.write(i);
        delay(20);
      }
      delay(1000);
      myServo.write(pos2);
      delay(1500);
      myServo.write(pos1);
      switchState = 0;
      count = 0; // reset the whole loop
      Serial.print("Switch count reset to ");
      Serial.println(count);
    }
  }
}