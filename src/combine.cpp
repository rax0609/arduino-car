#include <Arduino.h>
#include <NewPing.h>
// #include "motor.h"

#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void motor(int LA, int LB, int RA, int RB) {
    analogWrite(9, LA);
    analogWrite(10, LB);
    analogWrite(6, RA);
    analogWrite(5, RB);
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
        motor(0, 0, 0, 0);
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
    if (sonar.ping_cm() > 20) {
        line_following();
    } else {
        // motor(0, 150, 150, 0);
        // delay(500);
        // motor(150, 0, 0, 150);
        // delay(500);
        
        // do {
        //     left(255);
        //     delay(1000);
        //     run(255);
        // } while () {
            
        // }
    }
}