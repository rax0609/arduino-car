#include <Arduino.h>
#include "motor.h"

const int left1 = 9;
const int left2 = 10;

const int right1 = 5;
const int right2 = 6;

// 向前
void run(int speed) {
    // 馬達1
    analogWrite(left1, speed);
    analogWrite(left2, 0);
    // 馬達2
    analogWrite(right1, speed);
    analogWrite(right2, 0);
}

// 向後
void back(int speed) {
    // 馬達1
    analogWrite(left1, 0);
    analogWrite(left2, speed);
    // 馬達2
    analogWrite(right1, 0);
    analogWrite(right2, speed);
}

void left(int speed) {
    // 馬達1
    analogWrite(left1, 0);
    analogWrite(left2, speed);
    // 馬達2
    analogWrite(right1, speed);
    analogWrite(right2, 0);
}

void right(int speed) {
    // 馬達1
    analogWrite(left1, speed);
    analogWrite(left2, 0);
    // 馬達2
    analogWrite(right1, 0);
    analogWrite(right2, speed);
}

void back_left(int speed) {
    // 馬達1
    analogWrite(left1, 0);
    analogWrite(left2, speed);
    // 馬達2
    analogWrite(right1, speed / 2);
    analogWrite(right2, 0);
}

void back_right(int speed) {
    // 馬達1
    analogWrite(left1, speed / 2);
    analogWrite(left2, 0);
    // 馬達2
    analogWrite(right1, 0);
    analogWrite(right2, speed);
}

// 停止
void stop() {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}

void motor(int leftForward, int leftBackward, int rightForward, int rightBackward) {
    analogWrite(left1, leftForward);
    analogWrite(left2, leftBackward);

    analogWrite(right1, rightForward);
    analogWrite(right2, rightBackward);
}