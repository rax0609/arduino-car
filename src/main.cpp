#include <Arduino.h>
#include <NewPing.h>
#include "motor.h"

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void line_following(int IR_L, int IR_R) {
    if (IR_L == 0 && IR_R == 0) {
        run(180);
    } else if (IR_L == 1 && IR_R == 0) {
        motor(130, 0, 0, 0);
    } else if (IR_L == 0 && IR_R == 1) {
        motor(0, 0, 130, 0);
    } else {
        stop();
        delay(500);
        back(130);
    }
}

void obstacle_avoidance() {
        delay(1000);
        stop();

        left(180);
        delay(500);
        stop();

        run(180);
        delay(1000);
        stop();

        right(180);
        delay(500);
        stop();

        run(180);
        delay(1000);
        stop();

        right(180);
        delay(500);
        stop();

        run(180);
        delay(1000);
        stop();

        left(180);
        delay(500);
        stop();
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
    unsigned int distance = sonar.ping_cm();
    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");
    Serial.print("IR_L: ");
    Serial.print(IR_L);
    Serial.print(" IR_R: ");
    Serial.println(IR_R);
    delay(1000);

    if (distance <= 15) {
        obstacle_avoidance();
    } else {
        line_following(IR_L, IR_R);
    }
}