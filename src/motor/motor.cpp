#include <Arduino.h>
#include "motor.h"

const int motor1_1 = 5;
const int motor1_2 = 6;
const int motor2_1 = 9;
const int motor2_2 = 10;

void setup() {
    pinMode(motor1_1, OUTPUT);
    pinMode(motor1_2, OUTPUT);
    pinMode(motor2_1, OUTPUT);
    pinMode(motor2_2, OUTPUT);
}

void loop() {
    analogWrite(5, HIGH);
}

// 向前
void run(int speed) {
    // 馬達1
    analogWrite(motor1_1, speed);
    analogWrite(motor1_2, 0);
    // 馬達2
    analogWrite(motor2_1, speed);
    analogWrite(motor2_2, 0);
}

// 向後
void back(int speed) {
    // 馬達1
    analogWrite(motor1_1, 0);
    analogWrite(motor1_2, speed);
    // 馬達2
    analogWrite(motor2_1, 0);
    analogWrite(motor2_2, speed);
}

void left(int speed) {
    // 馬達1
    analogWrite(motor1_1, speed);
    analogWrite(motor1_2, 0);
    // 馬達2
    analogWrite(motor2_1, 0);
    analogWrite(motor2_2, speed);
}

void right(int speed) {
    // 馬達1
    analogWrite(motor1_1, 0);
    analogWrite(motor1_2, speed);
    // 馬達2
    analogWrite(motor2_1, speed);
    analogWrite(motor2_2, 0);
}

// 停止
void stop() {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}