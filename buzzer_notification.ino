#define BUZZER_PIN 8  // Choisis la broche où tu as branché le buzzer actif

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.begin(9600); // Assure-toi que le baud rate est le même que dans Qt (9600)
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command == "ALERT") {
      // Buzzer ON pendant 2 secondes
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
}
