// Define pins for the first 74HC595
const int dataPin1 = 43;  // DS pin of the first 74HC595
const int clockPin1 = 41; // SH_CP pin of the first 74HC595
const int latchPin1 = 42; // ST_CP pin of the first 74HC595

// Define pins for the second 74HC595
const int dataPin2 = 46;  // DS pin of the second 74HC595
const int clockPin2 = 44; // SH_CP pin of the second 74HC595
const int latchPin2 = 45; // ST_CP pin of the second 74HC595

// Digit to segment encoding (common cathode)
const byte segmentMap[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  // Set pin modes for the first 74HC595
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(latchPin1, OUTPUT);

  // Set pin modes for the second 74HC595
  pinMode(dataPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(latchPin2, OUTPUT);
}

void loop() {
  // Display numbers 0-99 on the 7-segment displays
  for (int num = 0; num < 100; num++) {
    int tens = num / 10;   // Tens place
    int units = num % 10;  // Units place

    displayDigit1(tens);   // Display tens place on the first 7-segment display
    displayDigit2(units);  // Display units place on the second 7-segment display
    delay(1000);           // Wait for 1 second
  }
}

void displayDigit1(int digit) {
  // Ensure digit is within 0-9
  if (digit < 0 || digit > 9) return;

  // Get the segment byte for the digit
  byte segments = segmentMap[digit];

  // Send the segment byte to the first 74HC595
  digitalWrite(latchPin1, LOW); // Prepare to send data
  shiftOut(dataPin1, clockPin1, MSBFIRST, segments); // Send data
  digitalWrite(latchPin1, HIGH); // Latch data
}

void displayDigit2(int digit) {
  // Ensure digit is within 0-9
  if (digit < 0 || digit > 9) return;

  // Get the segment byte for the digit
  byte segments = segmentMap[digit];

  // Send the segment byte to the second 74HC595
  digitalWrite(latchPin2, LOW); // Prepare to send data
  shiftOut(dataPin2, clockPin2, MSBFIRST, segments); // Send data
  digitalWrite(latchPin2, HIGH); // Latch data
}
