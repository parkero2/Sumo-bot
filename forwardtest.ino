//Declare pins
//Left side motor variabe declaration
int LSp = 5;
int Lf = 6;
int Lb = 7;
//Right side motor variable declaration
int RSp = 3;
int Rf = 2;
int Rb = 4;
//Sensor declarations
//Ultrasonic
int echoPin = 11;
int trigPin = 12;
//IR sensors
int BR = A3;
int FR = A2;
int FL = A1;
int BL = A0;
//IR VLAUES
int BackRightIR = analogRead(BR);
int FrontRightIR = analogRead(FR);
int FrontLeftIR = analogRead(FL);
int BackLefttIR = analogRead(BL);

void StopMotors() { //Turn all of the motors off (uses H-bridge)
    Serial.println("Stopping...");
    digitalWrite(Lf, LOW);
    digitalWrite(Lb, LOW);
    digitalWrite(Rb, LOW);
    digitalWrite(Rf, LOW);
    delay(200);
}

void ChangeSpeed(int speed) { //Change the speed of the motors
    Serial.println("Changing speed...");
    analogWrite(LSp, speed);
    analogWrite(RSp, speed);
}

void Forward() {
    Serial.println("Forward...");
    StopMotors();
    digitalWrite(Rf, HIGH);
    digitalWrite(Lf, HIGH);
}

void Backward() {
    Serial.println("Backward");
    StopMotors();
    digitalWrite(Rb, HIGH);
    digitalWrite(Lb, HIGH);
}

void Left() {
    Serial.println("Left...");
    StopMotors();
    digitalWrite(Rf, HIGH);
    digitalWrite(Lb, HIGH);
}

void Right() {
    Serial.println("Right...");
    StopMotors();
    digitalWrite(Rb, HIGH);
    digitalWrite(Lf, HIGH);
}

int SonicSense() { //Get a ultrasonic reading and return it in mm
    Serial.println("Ultrasonicing...");
    digitalWrite(trigPin, LOW);
    delayMicroseconds(20);
    digitalWrite(trigPin, HIGH);
    int mm = pulseIn(echoPin, HIGH) * 0.017;
    digitalWrite(trigPin, LOW);
    return mm;
}

boolean LineSense(boolean checkRes) { //Check all sensors
    Serial.println("Linesensors...");
    int BackRightIR = analogRead(BR);
    int FrontRightIR = analogRead(FR);
    int FrontLeftIR = analogRead(FL);
    int BackLefttIR = analogRead(BL);
    if (checkRes) {
        if (BackLefttIR > 800 || FrontLeftIR > 800 || BackRightIR > 800 || FrontRightIR > 800) {
            return true;
        }
        else {
            return false;
        }
    }
}

void setup() {
    pinMode(LSp, OUTPUT);
    pinMode(RSp, OUTPUT);
    pinMode(Lf, OUTPUT);
    pinMode(Lb, OUTPUT);
    pinMode(Rf, OUTPUT);
    pinMode(Rb, OUTPUT);
    pinMode(trigPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    ChangeSpeed(100);
    Forward();
    delay(999);
    /*
   if (SonicSense() < 100 && !LineSense(true)) {
       ChangeSpeed(100);
       Forward();
       if(SonicSense() < 20) {
           ChangeSpeed(120);
       }
   }
   else if (LineSense(true)) {
       if (FrontLeftIR < 800) {
           //On line, move off
           Backward();
           analogWrite(RSp, 100); //Veer to the right
           delay(200);
           ChangeSpeed(200); //Reset speed to normal
       }
       else if (FrontRightIR < 800) { //My tests showed values less than 800 were typically on the line
           //On line, move off
           Backward();
           analogWrite(LSp, 100); //Veer to the right
           delay(200);
           ChangeSpeed(200); //Reset speed to normal
       }
   }
   else { //Start spinning to find people
       ChangeSpeed(10);
       Left();
       delay(100);
   }*/
}
