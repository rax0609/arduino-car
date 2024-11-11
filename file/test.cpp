#include <Arduino.h>

const int motor1_1 = 5;
const int motor1_2 = 6;
const int motor2_1 = 9;
const int motor2_2 = 10;

void motor(int LA, int LB, int RA, int RB) {
    analogWrite(9, LA);
    analogWrite(10, LB);
    analogWrite(6, RA);
    analogWrite(5, RB);
}

void run(int speed) {
    analogWrite(5, speed);
    analogWrite(9, speed);
}

void left(int speed) {
    analogWrite(5, 0);      // 停止右側馬達
    analogWrite(6, speed);  // 反轉右側馬達
    analogWrite(9, speed);  // 正轉左側馬達
    analogWrite(10, 0);     // 停止左側馬達
}

void right(int speed) {
    analogWrite(5, speed);  // 正轉右側馬達
    analogWrite(6, 0);      // 停止右側馬達
    analogWrite(9, 0);      // 停止左側馬達
    analogWrite(10, speed); // 反轉左側馬達
}

void stop() {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}

void setup() {
    pinMode(motor1_1, OUTPUT);
    pinMode(motor1_2, OUTPUT);
    pinMode(motor2_1, OUTPUT);
    pinMode(motor2_2, OUTPUT);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
}

void loop() {
    // int IR_L = digitalRead(A0);
    // int IR_R = digitalRead(A1);

    // if (IR_L == 0 && IR_R == 0) {
    //     run(255);
    // } else {
    //     stop();
    // }

    run(255);
    delay(1000);
    right(255);
    delay(1000);
    run(255);
}