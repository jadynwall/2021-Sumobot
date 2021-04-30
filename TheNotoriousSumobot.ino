#include <NewPing.h>
#define MAX_DISTANCE 200 // Maximum distance to ping for (cm)
#define SONAR_NUM 1 // Number of sensors

NewPing sonar[SONAR_NUM] = { // sensor object array
  NewPing(9, 10, MAX_DISTANCE) // Trigger pin, Echo pin, max distance to ping
};

//line sensor uses pin A0
const int QRD1114_PIN = A0;

//Define motor functions
void forward();
void backward();
void turn();
void motoroff();
////////////////////////////////////////////
void setup() {
  //motor setup
  pinMode(4, OUTPUT); //pinMode() configures pin to behave as output
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  
  //line sensor setup
  Serial.begin(9600); //Sets data rate for serial data transmission
  pinMode(QRD1114_PIN, INPUT); //pinMode() configures pin to behave as input
  
  //wait 5 seconds to start
  delay(5000);
}

void loop() {
  //line sensor
  int proximityADC = analogRead(QRD1114_PIN); // Take voltage of noise
  float proximityV = (float)proximityADC * 5.0 / 1023.0; //determines proximity voltage
  Serial.println(proximityV); //for troubleshooting
  
  //ultrasonic sensor
  int u1 = sonar[0].ping_cm(); //gets distance

  //stop at black line
  if (proximityV > 3){
    backward();
    delay(500);
    turn();
    delay(200);
  }
  
  //motor
  if(u1<50){
    forward();
  } else if (u1 > 50){
    turn();
    delay(100);
    motoroff();
    delay(100);
  }

 

  delay(100);
}

/////////////////////////////////////////////
void forward(){
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);

  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
void backward(){
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void turn(){
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);

  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
void motoroff(){
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}
