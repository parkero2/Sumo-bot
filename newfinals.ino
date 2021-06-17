//Left side motor variabe declaration
int LSpeed = 5;
int Lfront = 6;
int Lback = 7;
//Right side motor variable declaration
int RSpeed = 3;
int RFront = 2;
int Rback = 4;
//Sensor declarations
//Ultrasonic
#define echoPin A0
#define trigPin A1
//IR sensors
int BR = A5;
int FR = A4;
int FL = A3;
int BL = A2;

int returnedVals[4];
int mm = 0;
const int speedOffset = 96;

void stopMotors() {
  digitalWrite(Lfront, LOW);
  digitalWrite(RFront, LOW);
  digitalWrite(Rback, LOW);
  digitalWrite(Lback, LOW);
  delay(100);
}

void SetSpeed(int speedin) {
  analogWrite(LSpeed, (speedin /100) * speedOffset);
  analogWrite(RSpeed, speedin);
}

void Forward() {
  stopMotors();
  digitalWrite(Lfront, HIGH);
  digitalWrite(RFront, HIGH);
}

void Backward() {
  stopMotors();
  digitalWrite(Lback, HIGH);
  digitalWrite(Rback, HIGH);
}

void Right() {
  stopMotors();
  digitalWrite(Lfront, HIGH);
  digitalWrite(Rback, HIGH);
}

void Left() {
  stopMotors();
  digitalWrite(Lback, HIGH);
  digitalWrite(RFront, HIGH);
}

int UltraSonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    mm = pulseIn(echoPin, HIGH, 30000) * 0.17;
    return mm;
}
int * IRSense() {
    returnedVals[0] = digitalRead(BR);
    returnedVals[1] = digitalRead(FR);
    returnedVals[2] = digitalRead(FL);
    returnedVals[3] = digitalRead(BL);
    return returnedVals;
    //IRSense will get a reading from all four of the infared sensors located on the bottom of the bot, then returns the data in the format of an array.
}

void setup() {
    // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RSpeed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(Lfront, OUTPUT);
  pinMode(Rback, OUTPUT);
  pinMode(Lback, OUTPUT);
  pinMode(RFront, OUTPUT);
  pinMode(LSpeed, OUTPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
  IRSense();
  if (UltraSonic() < 80 && returnedVals[0] < 800 && returnedVals[1] < 800 && returnedVals[2] < 800 && returnedVals[3] < 800) {
     Forward();
     SetSpeed(100); //Charge
  }
  else {
    SetSpeed(50);
    Left();
  }
  delay(100);
}
