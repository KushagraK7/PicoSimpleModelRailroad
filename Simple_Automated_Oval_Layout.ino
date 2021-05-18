/*
 * Arduino program to control a model train running in a basic oval loop with the help of a feedback sensor.
 * Made by Tech Build: https://www.youtube.com/channel/UCNy7DyfhSD9jsQEgNwETp9g?sub_confirmation=1
 * 
 * You can find more projects here: https://www.instructables.com/member/KushagraK7/
 * 
 */

int s; //Integer variable to store train's speed in the range from 0 to 255.
int maxSpeed = 100;//Integer variable to store the maximum speed the train will reach(max is 255 and is very fast).
int t = 5; //Time delay(pause, in seconds) between each loop of operation, from start to stop.

#define A 8 //'A' and 'B' are direction control pins connected to the motor driver.
#define B 9
#define PWM 7 //Motor speed control pin connected to the 'EN' pin of the motor driver.
#define Sensor 1 //Input pin for connecting the 'sensored' track.

void motor_go(){
 if(s>=1&&s<=255){
  digitalWrite(B,LOW);
  digitalWrite(A,HIGH);
  analogWrite(7,s);
 }
 if(s<=-1&&s>=-255){
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  analogWrite(7,-s);
 }
 if(s==0){
  digitalWrite(B,LOW);
  digitalWrite(A,LOW);
  analogWrite(7,s);
 }
 
 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);

  pinMode(Sensor,INPUT);

  pinMode(25, OUTPUT);//Added for Pico, sice it has no onboard POWER LED.

  digitalWrite(25, HIGH);//Using the LED on pin GP25 as a power indicator.

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  for(s=s;s<=20;s++){ //Starting the train.
    motor_go();
    delay(500);
  }

  delay(5000);

  for(s=s;s<=60;s++){ //Speeding up a bit.
    motor_go();
    delay(500);
  }

  delay(1000);

  while(digitalRead(Sensor)==LOW); //Wait for the train to cross the 'sensored' track.

  for(s=s;s<=maxSpeed;s++){ //Speeding up the train to maximum speed value set in the beginning.
    motor_go();
    delay(500);
  }

  delay(1000);
  while(digitalRead(Sensor)==LOW); //Wait for the train to cross the 'sensored' track.

  delay(2000);

  for(s=s;s!=80;s--){ //Slow down the train a bit.
    motor_go();
    delay(1000);
  }

  delay(4000);
  while(digitalRead(Sensor)==LOW); //Wait for the train to cross the 'sensored' track.

  for(s=s;s!=60;s--){ //Slow down the train furthur.
    motor_go();
    delay(500);
  }

  delay(4000);

  for(s=s;s!=20;s--){ //Slow down the train, preparing to stop.
    motor_go();
    delay(500);
  }
  
  while(digitalRead(Sensor)==LOW); //Wait for the train to cross the 'sensored' track.
  
  for(s=s;s!=0;s--){ //Reduce the voltage on the tracks to just let the locomotive lights turned on.
    motor_go();
    delay(500);
  }


  delay(1000*t); //Wait for the set time before starting all over again.
}
