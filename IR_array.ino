// Define variables for each sensor
int sen1, sen2, sen3, sen4, sen5, sen6, sen7, sen8, sen9, sen10, sen11, sen12;

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Configure A0 to A11 as input pins (not strictly necessary as they are input by default)
  for (int i = A0; i <= A11; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  // Read values from each analog pin and assign to respective variables
  sen1 = analogRead(A0);
  sen2 = analogRead(A1);
  sen3 = analogRead(A2);
  sen4 = analogRead(A3);
  sen5 = analogRead(A4);
  sen6 = analogRead(A5);
  sen7 = analogRead(A6);
  sen8 = analogRead(A7);
  sen9 = analogRead(A8);
  sen10 = analogRead(A9);
  sen11 = analogRead(A10);
  sen12 = analogRead(A11);

  // Print the values to the serial monitor
  Serial.print("sen1: "); Serial.print(sen1); Serial.print(" ");
  Serial.print("sen2: "); Serial.print(sen2); Serial.print(" ");
  Serial.print("sen3: "); Serial.print(sen3); Serial.print(" ");
  Serial.print("sen4: "); Serial.print(sen4); Serial.print(" ");
  Serial.print("sen5: "); Serial.print(sen5); Serial.print(" ");
  Serial.print("sen6: "); Serial.print(sen6); Serial.print(" ");
  Serial.print("sen7: "); Serial.print(sen7); Serial.print(" ");
  Serial.print("sen8: "); Serial.print(sen8); Serial.print(" ");
  Serial.print("sen9: "); Serial.print(sen9); Serial.print(" ");
  Serial.print("sen10: "); Serial.print(sen10); Serial.print(" ");
  Serial.print("sen11: "); Serial.print(sen11); Serial.print(" ");
  Serial.print("sen12: "); Serial.print(sen12); Serial.print(" ");
  Serial.println(); // New line after all values are printed

  delay(100); // Wait for 1 second before the next reading
}
