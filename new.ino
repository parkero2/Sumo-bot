//PIN DECLARATION
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
int echoPin = A0;
int trigPin = A1;
//IR sensors
int BR = 12;
int FR = 11;
int FL = 10;
int BL = 9;
int returnedVals[];
//END OF PIN DECLARATION
int selfPilot = A2; //If A2 is connected to +5v it will enable the 'machine learning code' REF: https://www.arduino.cc/en/AI/HomePage. This is just an attempt.
int ErrPin = A3; //This pin has an LED attached and will be set to high if the arduino has sensed something
int mm = 0;
//Motor function declarations
void ChangeSpeed(int MSpeed) {
    analogWrite(LSp, MSpeed);
    analogWrite(RSp, MSpeed);
}

void HaltMotors() {
    ChangeSpeed(0);
    digitalWrite(Lf, LOW);
    digitalWrite(Rf, LOW);
    digitalWrite(Rb, LOW);
    digitalWrite(Lb, LOW);
}

void Forward() {
    HaltMotors();
    digitalWrite(Lf, HIGH);
    digitalWrite(Rf, HIGH);
}

void Backward() {
    HaltMotors(); 
    digitalWrite(Lb, HIGH);
    digitalWrite(Rb, HIGH);
}

void Left() {
    HaltMotors();
    digitalWrite(Lb, HIGH);
    digitalWrite(Rf, HIGH);
}

void Right() {
    HaltMotors();
    digitalWrite(Lf, HIGH);
    digitalWrite(Rb, HIGH);
}

void swerve(int offset) {
    //Offset is the % of the speed the opposite side is set to. Eg, if RSp is 130, and offset is -50 then LSp will be set to 65. Half of RSp
    if (offset < 100 && offset > -100) {
        //This ensures that no values passed into the functions exceed to 100% differential limit
        if (offset == 0) {
            if (analogRead(RSp) > analogRead(LSp)) {
                ChangeSpeed(analogRead(RSp));
            }
            else {
                ChangeSpeed(analogRead(LSp));
            }
        }
        else if (offset < 0) {
            swerve(0); //resets both motors to the same speed
            //This means that the offset is a negative interger and needs to swerve to the left
            analogWrite(LSp, (analogRead(RSp) / 100 * offset) * -1); //Changes speed and ensures it is a positive interger
        }
        else {
            swerve(0); //resets both motors to the same speed
            //Offset is positive, swerve to the right
            analogWrite(LSp, analogRead(RSp) / 100 * offset);
        }
    }
}
//End of motor function declarations
//sensor declarations
int * IRSense() {
    returnedVals[0] = digitalRead(BR);
    returnedVals[1] = digitalRead(FR);
    returnedVals[2] = digitalRead(FL);
    returnedVals[3] = digitalRead(BL);
    return returnedVals;
    //IRSense will get a reading from all four of the infared sensors located on the bottom of the bot, then returns the data in the format of an array.
}

boolean checkIRVals(boolean compensate) {
    IRSense();
    if (!compensate){
        for (int i = 0; i < 4; i++) {
            if (returnedVals[i] == 1) {
                digitalWrite(ErrPin, HIGH);
                return true;
            }
        }
        digitalWrite(ErrPin, LOW);
        return false;
    }
    else {
        if (checkIRVals(false)) {
            digitalWrite(ErrPin, HIGH);
        }
        else {
            digitalWrite(ErrPin, LOW);
        }
        //There's a line being sensed
        if (returnedVals[0] == 1) {
            //Back right HIGH
            swerve(-50);
            Forward();
            delay(500);
            HaltMotors();
        }
        else if  (returnedVals[1] == 1) {
            //Front right HIGH
            swerve(-50);
            Backward();
            delay(500);
            HaltMotors();
        }
        else if (returnedVals[2] == 1) {
            //Front left HIGH
            swerve(50);
            Backward();
            delay(500);
            HaltMotors();
        }
        else {
            //Back left HIGH
            swerve(50);
            Forward();
            delay(500);
            HaltMotors();
        }
    }
}

int UltraSonic() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    mm = pulseIn(echoPin, HIGH) * 0.17;
    if (mm < 80) {
        digitalWrite(ErrPin, HIGH);
    }
    else {
        digitalWrite(ErrPin, LOW);
    }
    return mm;
    //When the function UltraSonic() is called, the above code with run. The arduino sends a 10 microsecond pulse to the tiggerpin of the ultrasonic sesor then awaits a return pulse fron the echo pin. This is then multiplied by 0.17 to get the distance in mm.
}
//end of sensor functions

void setup() {
    Serial.begin(9600);
    pinMode(LSp, OUTPUT);
    pinMode(Lb, OUTPUT);
    pinMode(Lf, OUTPUT);
    pinMode(RSp, OUTPUT);
    pinMode(Rb, OUTPUT);
    pinMode(Rf, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(ErrPin, OUTPUT);
}

void loop() {
    if (digitalRead(selfPilot)) {
        //The switch is closed
        while (true) {
            //A while loop prevents the arduino from constantly checking the switch state. This means the reset button will need to be pressed to take effect
        }
    }
    else {
        while (true) {
            checkIRVals(true); //This function with a true argument means that it will detect lines and then try to compenstae for any errors
        }
    }
}