#include "letterCommands.h"
#include "config.h"

#include <Servo.h>

#define AI1 12 
#define AI2 11
#define BI1 10
#define BI2 9
#define pwmA A7
#define pwmB A6
#define stdby 4

#define servoXPin A2
#define servoYPin A3

Servo servoX;
Servo servoY;

bool testMode = false;

const int millisPerPoint = 1;
const int centerServoAngle = 100;

const int yAngleMax = 80;
const int yAngleMin = 120;

const int penDownAngle = 136;
const int penUpAngle = penDownAngle-10;


void setup() {

  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
  
  servoX.write(centerServoAngle);
  servoY.write(penUpAngle);
  
  Serial.begin(9600);
  
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(stdby, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(pwmA, OUTPUT);
  
  analogWrite(pwmA, 255);
  analogWrite(pwmB, 255);
  digitalWrite(stdby, HIGH);

  delay(3000);
  
  if (!testMode) {
    parseCommands(); 
    drawCommand(0);   
    
//  after drawing all commands:
    servoY.write(penUpAngle);
    servoX.detach();
    servoY.detach();
    carStop();
  }
  

  
}

int minY = 10000;
int maxY = -10000;

String currentCommand;

int xPos = 0; //current x-position of car
int numCommands; 

/*  gets minimum and maximum Y positions of letter commands,
 *  initiates letter command drawing
 */
void parseCommands() {

  
  
  //get total number of commands (including pen up/down)
  numCommands = sizeof(letterCommands)/sizeof(letterCommands[0]);

  for (int i = 0; i < numCommands; i++) { //for each command:
    //if letterCommand is not pen up ([0,NULL]):
    if (letterCommands[i][0]!=0 && letterCommands[i][1]!=NULL) {
      //check values against min/max
      if (letterCommands[i][1] < minY) {
        minY = letterCommands[i][1];
      }
      if (letterCommands[i][1] > maxY) {
        maxY = letterCommands[i][1];
      }
    }
  }
  Serial.print(minY);
  Serial.print(",");
  Serial.println(maxY);
}

void drawCommand(int cmd) {
  Serial.print("Command #");
  Serial.print(cmd);
  Serial.print(": ");

  //check if current command is pen up ([0,NULL])
  if (letterCommands[cmd][0] == 0 && letterCommands[cmd][1] == NULL) {
    Serial.println("PEN UP");
    servoY.write(penUpAngle);
    currentCommand = "move";
    drawCommand(cmd+1); //move to next command
    return;
  }
  if (currentCommand == "move") {
    Serial.print("MOVE TO: ");
  } else {
    Serial.print("LINE TO: ");
  }
  
  int xVal = letterCommands[cmd][0]; //get x-position for this command
  int xChange = xVal-xPos; //get change in horizontal position
  if (xChange > 0) { //if positive change:
    carBack();
  } else if (xChange < 0) { //if negative change:
    carForward();
  } 
  
  int yVal = letterCommands[cmd][1]; //get y-position for this command
  int yMap = map(yVal, minY, maxY, yAngleMax, yAngleMin); //calculate servo angle
  servoX.write(yMap); // move servo
  Serial.print(xVal);
  Serial.print(",");
  Serial.print(yMap);
 

  delay(abs(xChange*millisPerPoint)); //wait for horizontal motion according to degree of change
  carStop(); //stop the car

  if (currentCommand == "move") {
    servoY.write(penDownAngle);
    Serial.print(" PEN DOWN");
  }
  
  Serial.println();
  
  xPos = xVal; //update current x-position
  currentCommand = "line";
  delay(40);
  
  if (cmd+1 < numCommands) { //if current command is not the last:
    drawCommand(cmd+1); //move to next command
  }
  carStop();
}


void driveCar(int dirNum) {
  if (dirNum == 48 || dirNum == 0) {
//    parseCommands();
    drawCommand(0);
  } 
}

bool centralConnected = false;

void loop() {
  if (Serial.available() && testMode) {
    char servoChar = Serial.read();
    int num = Serial.parseInt();

    if ((String)servoChar == "x") {
      servoX.write(map(num,0,1000,yAngleMin,yAngleMax));
      delay(250);
    } else if ((String)servoChar == "y") {
      servoY.write(num);
      delay(250);
    } else if ((String)servoChar == "m") {
      int xChange = num-xPos;
      Serial.print("Moving by: ");
      Serial.println(xChange);
      xPos = num;
      if (xChange < 0) {
        carBack();
        delay(xChange*millisPerPoint*-1);
        carStop();
      } else if (xChange > 0) {
        carForward();
        delay(xChange*millisPerPoint);
        carStop();
      }
    }
    Serial.readString();
  }
}

void carBack() {
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
}

void carForward() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void carRight() {
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
}

void carLeft() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
}

void carStop() {
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, LOW);
}
