

//*********************************
// Recycle+   
// Esperino EPAL Giannitson
// BPLus
//*********************************

#include <Servo.h>


Servo pipeServo;  // create servo object to control a servo


// define the variables
int sensorInd = A0; 
int indValue;
long duration;
int distance;
int sensorState = 0;
float metalDetected;
int n=0;
int d=300;
int speed=255;
int cdPin1 = 3;
int cdPin2 = 2;
int irsensor=4;
int servoPin = 6;
int trigPin = 7;
int echoPin = 9;
int enA = 10;
int ledMetal = 11;
int ledPlastic = 12;
int ledPaper = 13;

void setup() {
pipeServo.attach(servoPin);  
pinMode(cdPin1, OUTPUT);
pinMode(cdPin2, OUTPUT);
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);    
pinMode(enA, OUTPUT);
pinMode(irsensor, INPUT);
pinMode(ledMetal, OUTPUT);
pinMode(ledPlastic, OUTPUT);
pinMode(ledPaper, OUTPUT);
Serial.begin(9600); 		// Starts the serial communication
pipeServo.write(90);          // turn tube to initial position of 90 degrees
            
}

void loop() {
  digitalWrite(ledMetal, LOW);
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);				// Sets the trigPin on HIGH state for 2 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);	
  digitalWrite(trigPin, LOW);			
  duration = pulseIn(echoPin, HIGH);	// Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration*0.034/2;		// Calculating the distance
  Serial.print("Distance: ");			// Prints the distance on the Serial Monitor
  Serial.println(distance);
  delay(800);
  if (distance<=4){
    digitalWrite(irsensor, LOW);
    //object detected in the slot
    indValue=analogRead(sensorInd);		//Save value that is read from the analog pin A0 to the variable indValue
    delay(10);
    metalDetected = (float)indValue*100/1024.0; 
    if(indValue>=250){
      Serial.println("Metal Detected");
      digitalWrite(ledMetal, HIGH);
      digitalWrite(cdPin1, LOW);
      digitalWrite(cdPin2, HIGH);
      analogWrite(enA, speed); 
      delay(d);
      digitalWrite(cdPin2, LOW);
      delay(500);
      digitalWrite(cdPin1, HIGH);
      analogWrite(enA, speed); 
      delay(d);
      digitalWrite(cdPin1, LOW);
      analogWrite(enA, speed); 
    }
    else{
        digitalWrite(irsensor, HIGH); // turn on the IR sensor
        sensorState = digitalRead(irsensor);		// read the state of the IR sensor:
        if (sensorState == LOW) {    			// check if the sensor beam is broken - if it is, the sensorState is LOW:
          // if the sensor beam is broken it is paper
          digitalWrite(ledPaper, HIGH);
          Serial.println("Paper Detected");
          digitalWrite(irsensor, LOW); 			// turn off the IR sensor 
          pipeServo.write(180);              		// turn tube to position 180 degrees
          delay(150);						// waits 15 ms for the servo to reach the position
          //open the gate and close it
          digitalWrite(cdPin1, LOW);
          digitalWrite(cdPin2, HIGH);
          analogWrite(enA, speed); 
          delay(d);
          digitalWrite(cdPin2, LOW);
          delay(500);
          digitalWrite(cdPin1, HIGH);
          analogWrite(enA, speed); 
          delay(d);
          digitalWrite(cdPin1, LOW);
          analogWrite(enA, speed); 
          digitalWrite(ledPaper, LOW);  
          pipeServo.write(90);         			//return pipe to initial position     
          
        }
        else {
          Serial.println("Plastic Detected");
          digitalWrite(ledPlastic, HIGH);  
          pipeServo.write(0);              	// turn tube to position 0 degrees
          delay(150); 					// waits 15 ms for the servo to reach the position     
          //open the gate and close it
          digitalWrite(cdPin1, LOW);
          digitalWrite(cdPin2, HIGH);
          analogWrite(enA, speed); 			// set the speed to a lower value
          delay(d);
          digitalWrite(cdPin2, LOW);
          delay(500);
          digitalWrite(cdPin1, HIGH);
          analogWrite(enA, speed); 
          delay(d);
          digitalWrite(cdPin1, LOW);
          analogWrite(enA, speed); 
          digitalWrite(ledPlastic, LOW);
          //return pipe to initial position
          pipeServo.write(90);              	// turn tube to initial position 
          delay(15); 					// waits 15 ms for the servo to reach the position
        }
                            
    }

              
  } 
}





 





