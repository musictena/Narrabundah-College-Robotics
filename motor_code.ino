//include motor library
#include <AFMotor.h>

#define Trig 12
#define Echo 13

#define ENA 5
#define ENB 6
#define IN1 3
#define IN2 4
#define IN3 2
#define IN4 7

float cm; //Distance variable
float temp; //

void setup() {
  //setup the serial monitor at 9600 bauts
  Serial.begin(9600);

  //initalise the variables as either an output or an input
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  //turn the ultrasonic sensor's trigger on LOW before triggering the first pulse by turning it on HIGH
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  //make the varible 'temp' be equal to the pulsing echo signal so that the dsitance variable can be used
  temp = float(pulseIn(Echo, HIGH));
  cm = (temp * 17 ) / 1000;

  //when an object is less than 30cm in front of the ultrasonic sensor but more than 10; do the 'back' function and 'left' function
  if (cm < 30 && cm > 10)
  {
    Back();
    delay(500);
    Left();
    delay(200);
  }
  // else if an object is equal or more than 30 cm, continue going forwards (through a function)
  if (cm >= 30)
  {
    Forward();
    delay(100);
  }

  //if the object is less than 10 cm away, do the stop fucntion
  if (cm < 10)
  {
    STOP();
  }
  // print on serial monitor the distance between the ultraosnic and the object as well as the rate of trigger pulses
  Serial.print("Echo =");
  Serial.print(temp);
  Serial.print(" | | Distance = ");
  Serial.print(cm);
  Serial.println("cm");
  delay(100);
}

// for the function; forward, have all motors move forwards, and hence display on serial monitor
void Forward() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

// for the function, back, have all motors go backwards and display function on serial monitor
void Back() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

// for the function, left, have the right motors move forwards while the right motors stop, display on serial monitor
void Left() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}

// for the function, right, have the right motors stop while the left motors move forwards, diaply fucntion on serial monitor
void Right() {
  analogWrite(ENA, 220);
  analogWrite(ENB, 220);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

//for the function, stop, have all motors stop and display stop on serial monitor
void STOP() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("STOP");
}
