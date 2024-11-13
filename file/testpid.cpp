#include <Arduino.h>
#include <NewPing.h>
#include "motor.h"

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// PID參數
float Kp = 2.0;
float Ki = 0.5;
float Kd = 1.0;
float previous_error = 0;
float integral = 0;

void line_following(int IR_L, int IR_R) {
    int error = IR_L - IR_R;
    integral += error;
    float derivative = error - previous_error;
    float output = Kp * error + Ki * integral + Kd * derivative;
    previous_error = error;

    if (output > 0) {
        motor(180 - output, 0, 0, 0);
    } else if (output < 0) {
        motor(0, 0, 180 + output, 0);
    } else {
        run(150);
    }
}

void obstacle_avoidance() {
    unsigned int distance = sonar.ping_cm();
    if (distance <= 15) {
        stop();
        delay(1000);
        motor(0, 0, 180, 0); // 向右轉
        delay(500);
        run(150);
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
    unsigned int distance = sonar.ping_cm();
    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);

    // Serial.print("IR_L: ");
    // Serial.print(IR_L);
    // Serial.print(" IR_R: ");
    // Serial.println(IR_R);
    // delay(1000);

    line_following(IR_L, IR_R);
    obstacle_avoidance();

    // 調整PID參數
    Serial.print("Kp: ");
    Serial.print(Kp);
    Serial.print(" Ki: ");
    Serial.print(Ki);
    Serial.print(" Kd: ");
    Serial.println(Kd);

    // 根據需要調整這些值
    Kp += 0.1;
    Ki += 0.01;
    Kd += 0.01;

    // 防止參數過大
    if (Kp > 10) Kp = 0;
    if (Ki > 1) Ki = 0;
    if (Kd > 1) Kd = 0;
}