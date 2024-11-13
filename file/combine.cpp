#include <Arduino.h>
#include <NewPing.h>
// #include "motor.h"

#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void motor(int leftForward, int leftBackward, int rightForward, int rightBackward) {
    analogWrite(9, leftForward);
    analogWrite(10, leftBackward);
    analogWrite(6, rightForward);
    analogWrite(5, rightBackward);
}

void line_following() {
    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);

    if (IR_L == 0 && IR_R == 0) {
        motor(150, 0, 150, 0);
    } else if (IR_L == 1 && IR_R == 0) {
        motor(150, 0, 0, 0);
    } else if (IR_L == 0 && IR_R == 1) {
        motor(0, 0, 150, 0);
    } else {
        motor(255, 255, 255, 255);
    }
}

void setup() {
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void loop() {
    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);

    Serial.print("IR_L: ");
    Serial.print(IR_L);
    Serial.print(" IR_R: ");
    Serial.println(IR_R);

   // line_following();

   motor(0, 0, 180, 0);
    delay(1000);
}