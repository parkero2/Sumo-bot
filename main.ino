//Left side variabe declaration
int LSp = 5;
int Lf = 6;
int Lb = 7;
//Right side variable declaration
int RSp = 3;
int Rf = 2;
int Rb = 4;
//define speed ints lmao
int sped = 0;
//declare ultrasonic pins
#define echoPin 11
#define trigPin 12
long duration;
int distance;
//Declare line sensor pins
int linesense = 10;
//Reverse op
int reverseop = 0; //stopped, forward, backwards, left, right
int previousops[] = {0}; //Add some smart
//I am not declaring stuff anymore

int sonicsense() {
    //Sensor code bitvhhhhhhhklhsidghlkfdhng
    Serial.println("Sensing some random shit bitch");
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    if (distance < 10) {
        Serial.println("Ahhh wtf piss off bitch");
    }
    delay(100);
    return distance;
}

void change_speed(int speedgobrrrr) {
    sped = speedgobrrrr;
    analogWrite(LSp, sped);
    analogWrite(RSp, sped);
}
void stopmot() {
    //stop motors and wait 200 milliseconds
    reverseop = 0;
    analogWrite(LSp, 0);
    analogWrite(RSp, 0);
    digitalWrite(Lf, LOW);
    digitalWrite(Lb, LOW);
    digitalWrite(Rf, LOW);
    digitalWrite(Rb, LOW);
    Serial.println("Stopped");
    delay(200);
}

void Forward() {
    //um well it's a function labeled Forward. Seems self explanitory
    reverseop = 2;
    stopmot(); //This function is run on every movment function to essentially reset the motors and their speed
    Serial.println("Forward");
    analogWrite(LSp, 130);
    analogWrite(RSp, 130);
    digitalWrite(Lf, HIGH);
    digitalWrite(Rf, HIGH);
}
void Backward() {
    reverseop = 1;
    //Go Backwards?
    stopmot();
    Serial.println("Backward");
    analogWrite(LSp, 130);
    analogWrite(RSp, 130);
    digitalWrite(Lb, HIGH);
    digitalWrite(Rb, HIGH);
}
void Left() {
    //When executed, turns Left
    reverseop = 4; 
    stopmot();
    Serial.println("Left");
    analogWrite(LSp, 130);
    analogWrite(RSp, 130);
    digitalWrite(Lb, HIGH);
    digitalWrite(Rf, HIGH);
}
void Right() {
    //Idk if I need to explain this one
    reverseop = 1;
    stopmot();
    Serial.println("Left");
    analogWrite(LSp, 130);
    analogWrite(RSp, 130);
    digitalWrite(Lf, HIGH);
    digitalWrite(Rb, HIGH);
}

void toggledir() {
    if (reverseop == 0) {
        Serial.println("That's some weird shit. Not meant to be stopped.");
    }
    else if (reverseop == 1) {
        Serial.println("Switch to forward...");
        Forward();
    }
    else if (reverseop == 2) {
        Serial.println("Switch to back...");
        Backward();
    }
    else if(reverseop == 3) {
        Serial.println("Switch to left...");
        Left();
    }
    else if (reverseop == 4) {
        Serial.println("Switch to right...");
        Right();
    }
    else { 
        Serial.println("Um I have no idea wtf is happening. Shit.");
    }
}

void setup() {
    //Define pin modes, I chose not to use a for loop incase I need to move/modify modules on pins 
    pinMode(LSp, OUTPUT);
    pinMode(Lf, OUTPUT);
    pinMode(Lb, OUTPUT);
    pinMode(RSp, OUTPUT);
    pinMode(Rf, OUTPUT);
    pinMode(Rb, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
    //Declare some functions
    Serial.begin(9600); //Begin serial communication
}
//darkgreen to white
void loop() {
    //Loops lol
    Forward(); //execute the Forward function
    delay(1000); //delay for 1 second
    Backward(); //execute Backward function
    delay(1000);  //delay for a second
    //Add some logic
    if(sonicsense() < 5) {
        //Sensed somsething less than 5 cm away lmao


    }
    else {
        if (digitalRead(linesense) == 1) {
            toggledir(); //add some tactical manourvers
        }
        //Do something that gets you closed to other bots
    }
}

/**
 * CONTROLLER PIN | ARDUINO PIN | DECLARATION
 * PWMA           | D5          | LSp
 * A1             | D6          | Lf
 * A2             | D7          | Lb
 * PWMB           | D3          | RSp
 * B1             | D2          | Rf
 * B2             | D4          | Rb
 **/