#include <Servo.h>
#include <ezButton.h>

const int Speaker = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Speaker, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  playStart();
  Serial.println("playing start");
  delay(3000);
  Serial.println("playing Scored");
  playScoreSound();
  delay(2000);
  playGameOver(); 
  Serial.println("playing game over");
  delay(2000);

}


void playStart() {
  tone(Speaker, 800, 1000);
  delay(300);
  tone(Speaker, 1200, 1000);
  delay(300);
  tone(Speaker, 1600, 1000);
  delay(300);
  tone(Speaker, 2000, 2500);
}

void playScoreSound(){
  tone(Speaker, 800, 1000);
  tone(Speaker, 2000, 500);
}

void playGameOver() {
  tone(Speaker, 2000, 2500);
  delay(300);
  tone(Speaker, 1600, 1000);
  delay(300);
  tone(Speaker, 1200, 1000);
  delay(300);
  tone(Speaker, 800, 1500);
  delay(300);
  tone(Speaker, 600, 2500);
}