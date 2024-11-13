#include <Arduino.h>
#include <NewPing.h>
#include "motor.h"

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void line_following(int IR_L, int IR_R) {
    if (IR_L == 0 && IR_R == 0) {
        run(150);
    } else if (IR_L == 1 && IR_R == 0) {
        motor(180, 0, 0, 0);
    } else if (IR_L == 0 && IR_R == 1) {
        motor(0, 0, 180, 0);
    } else {
        stop();
    }
}

void setup() {
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    Serial.begin(9600);
}

void loop() {
    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);

    Serial.print("IR_L: ");
    Serial.print(IR_L);
    Serial.print(" IR_R: ");
    Serial.println(IR_R);
    delay(1000);

    line_following(IR_L, IR_R);
}