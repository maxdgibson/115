#include <Servo.h>
#include <ezButton.h>
#include <LiquidCrystal.h>

// Pin Definitions
const int SolenoidLeftFlip = 22;
const int SolenoidRightFlip = 23;
const int stepperPins[][4] = {{27, 28, 29, 30}, {31, 32, 33, 34}};
const int servoPin = 6;
const int buttonPins[] = {47, 48, 49};
const int IRPins[] = {A0, A1, A2, A3, A4};  // IR sensors for plunger, lost ball, and scoring
const int Speaker = 10;
//global variables to track steppers
int stepIndex1 = 0;
int stepIndex2 = 0;
//global audio integers:
const int gameOverFrequency = 220;  // Low pitch sound for game over
const int soundDuration = 500;  // Duration of the sounds in milliseconds
const int gameStartFrequency = 1000;
const int scoreFrequency = 2000;
const int scoreLowFreq = 800;
const int soundDurShort = 200;

// Game Variables
int score = 0;
enum GameState { WAITING, PLAYING, GAME_OVER };
GameState gameState = WAITING;

// Display and Actuator Objects
LiquidCrystal lcd(35, 36, 37, 38, 39, 40);
ezButton buttonStart(buttonPins[0]);
ezButton buttonLeftFlip(buttonPins[1]);
ezButton buttonRightFlip(buttonPins[2]);
Servo servoBallRelease;

void setup() {
  Serial.begin(9600);
  setupButtons();
  setupDisplays();
  setupActuators();
}

void loop() {
  handleButtons();
  handleSteppers();
  updateIRScoring();
  switch(gameState) {
    case WAITING:
      displayWelcome();
      break;
    case PLAYING:
      playStart();
      displayGamePlaying();
      break;
    case GAME_OVER:
      displayGameOver();
      playGameOver();
      break;
  }
}

void setupButtons() {
  buttonStart.setDebounceTime(100);
  buttonLeftFlip.setDebounceTime(100);
  buttonRightFlip.setDebounceTime(100);
}

void setupDisplays() {
  lcd.begin(16, 2);
  lcd.clear();
}

void setupActuators() {
  pinMode(SolenoidLeftFlip, OUTPUT);
  pinMode(SolenoidRightFlip, OUTPUT);
  servoBallRelease.attach(servoPin);
  servoBallRelease.write(0);  // Initial position

  // Set stepper motor pins to output
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      pinMode(stepperPins[i][j], OUTPUT);
    }
  }
  // IR sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(IRPins[i], INPUT);
  }
}

void handleButtons() {
  buttonStart.loop();
  buttonLeftFlip.loop();
  buttonRightFlip.loop();

  if (buttonStart.isPressed() && gameState == WAITING) {
    Serial.println("Start pressed");
    servoBallRelease.write(90);  // Release ball to plunger
    gameState = PLAYING;
  }

  if (buttonLeftFlip.isPressed()) {
    Serial.println("Left Flipper pressed");
    digitalWrite(SolenoidLeftFlip, HIGH);
  }
  if (buttonLeftFlip.isReleased()) {
    digitalWrite(SolenoidLeftFlip, LOW);
  }

  if (buttonRightFlip.isPressed()) {
    Serial.println("Right Flipper pressed");
    digitalWrite(SolenoidRightFlip, HIGH);
  }
  if (buttonRightFlip.isReleased()) {
    digitalWrite(SolenoidRightFlip, LOW);
  }
}

void handleSteppers() {
  if (gameState == PLAYING) {
    OneStep1(true);  // Continuously rotate stepper motor 1 in one direction
    OneStep2(true);  // Continuously rotate stepper motor 2 in one direction
    delay(10);  // Control speed of rotation
  }
}

void updateIRScoring() {
  static bool lastIRStates[5] = {false};
  for (int i = 0; i < 5; i++) {
    bool currentState = digitalRead(IRPins[i]);
    if (currentState && !lastIRStates[i]) {
      if (i == 2 || i == 3 || i == 4) {  // Scoring IRs
        score += 1;  // Increment score
        playScoreSound();  // Play scoring sound
      }
      if (i == 1) {  // Ball lost
        gameState = GAME_OVER;
      }
    }
    lastIRStates[i] = currentState;
  }
}

void displayGamePlaying(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("GOOD LUCK");
  lcd.setCursor(4, 1);
  lcd.print("GOOD LUCK");
}

void displayWelcome() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Start");
}

void OneStep1(bool clockwise) {
  static const int stepCount = 4; // Number of steps in the sequence
  static const int stepSequence[4][4] = { // Wave drive sequence for stepper motor
    {HIGH, LOW, LOW, LOW},  // Step 1
    {LOW, HIGH, LOW, LOW},  // Step 2
    {LOW, LOW, HIGH, LOW},  // Step 3
    {LOW, LOW, LOW, HIGH}   // Step 4
  };

  // Set each pin to the correct state from the sequence
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(stepperPins[0][pin], stepSequence[stepIndex1][pin]);
  }

  // Update step index for the next call
  if (clockwise) {
    stepIndex1 = (stepIndex1 + 1) % stepCount; // Move forward in the sequence
  } else {
    stepIndex1 = (stepIndex1 - 1 + stepCount) % stepCount; // Move backward in the sequence
  }
}


void OneStep2(bool clockwise) {
  static const int stepCount = 4; // Number of steps in the sequence
  static const int stepSequence[4][4] = { // Wave drive sequence for stepper motor
    {HIGH, LOW, LOW, LOW},  // Step 1
    {LOW, HIGH, LOW, LOW},  // Step 2
    {LOW, LOW, HIGH, LOW},  // Step 3
    {LOW, LOW, LOW, HIGH}   // Step 4
  };

  // Set each pin to the correct state from the sequence
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(stepperPins[1][pin], stepSequence[stepIndex2][pin]);
  }

  // Update step index for the next call
  if (clockwise) {
    stepIndex2 = (stepIndex2 + 1) % stepCount; // Move forward in the sequence
  } else {
    stepIndex2 = (stepIndex2 - 1 + stepCount) % stepCount; // Move backward in the sequence
  }
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
  tone(Speaker, scoreFrequency, soundDurShort);
  tone(Speaker, scoreLowFreq, soundDurShort);
  tone(Speaker, scoreFrequency, soundDurShort);
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

void displayGameOver() {
  lcd.setCursor(0, 0);
  lcd.print("Game Over!");
  delay(2000); // Show game over screen for 2 seconds
  
  // Reset game state and components for a new game
  gameState = WAITING;
  servoBallRelease.write(0);  // Reset servo to initial position to block the ball
  lcd.clear();  // Clear the display for the next message
  lcd.setCursor(0, 0);
  lcd.print("Press Start");  // Prompt to start a new game
}
