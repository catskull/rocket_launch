#include <Servo.h>

int startButton = 2;
int trigPin = 9;
int echoPin = 10;
int xServoCtrl = 6;
int yServoCtrl = 3;
int rocketMotor = 8;
int led = 13;

float x_cords[180];
float y_cords[45];

float pingTime;
float targetDistance;
float speedOfSound = 776.5; //miles per hour when temp is 77 degrees F

Servo x;
Servo y;

void setup() {                
   Serial.begin(9600);
   
   pinMode(led, OUTPUT);
   pinMode(startButton, INPUT);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(xServoCtrl, OUTPUT);
   pinMode(yServoCtrl, OUTPUT);
   pinMode(rocketMotor, OUTPUT);
   
   x.attach(xServoCtrl);
   y.attach(yServoCtrl);
}

void shoot() {
   digitalWrite(rocketMotor, HIGH);
   delay(51); 
   digitalWrite(rocketMotor, LOW);
}

float pingBack() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  
  pingTime = pulseIn(echoPin, HIGH); //in microseconds
  pingTime = pingTime/1000000.0; //convert ping time to seconds
  pingTime = pingTime/3600.0; //convert ping time to hours
  
  targetDistance = speedOfSound * pingTime; //calculate distance in miles
  targetDistance = targetDistance / 2.0; // only get time it takes to get to the target
  targetDistance = targetDistance*63360; //convert target distance to inches
  
  Serial.print("The distance to the target is: ");
  Serial.print(targetDistance);
  Serial.println(" inches");
  return targetDistance;
}

void sweep_y(){
  int pos = 45;
  for(pos = 45; pos < 90; pos += 1){
    y.write(pos);
    Serial.print("x is : ");
    Serial.println(pos);
    delay(10);
    y_cords[pos - 45] = pingBack();
    Serial.println(y_cords[pos - 45]);
//    pingBack();
    delay(10);
  }
}


void sweep_x(){
  int pos = 0;
  for(pos = 0; pos < 180; pos += 1){
    float temp  [1]
    x.write(pos);
    Serial.print("x is : ");
    Serial.println(pos);
    delay(10);
    x_cords[pos] = pingBack();
    delay(10);
  }
}
// the loop routine runs over and over again forever:
void loop() {
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  pingBack();
  delay(100);

//    shoot();

  
}
