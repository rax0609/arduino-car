#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
    
}

void loop() {
    delay(50);
    Serial.print("Ping: ");
    Serial.print(sonar.ping_cm());
    Serial.print("cm");

    if (sonar.ping_cm() < 20) {
        analogWrite(5, 255);
        analogWrite(9, 255);
    } else {
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(9, 0);
        analogWrite(10, 0);
    }
}