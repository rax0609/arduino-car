#include <Arduino.h>
#include <NewPing.h>
#include "motor.h"

// 設定超聲波傳感器的引腳
const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200;  // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// PID 控制器參數
float Kp = 0.6;  // 比例增益
float Ki = 0.1;  // 積分增益
float Kd = 0.3;  // 微分增益

float prevError = 0;  // 上次誤差
float integral = 0;    // 積分項
float derivative = 0;  // 微分項
float error = 0;       // 當前誤差

// PID 計算函數
float pidControl(float error) {
    integral += error;
    derivative = error - prevError;

    // 計算 PID 輸出
    float output = Kp * error + Ki * integral + Kd * derivative;

    // 保存當前誤差給下一次使用
    prevError = error;

    return output;
}

// 追蹤黑線的函數
void line_following(int IR_L, int IR_R, int IR_L2, int IR_R2) {
    // 計算誤差，這裡使用 IR_L 和 IR_R 來判斷左右偏差
    error = IR_L - IR_R;  // 假設誤差是兩側傳感器的差異

    // 用 PID 控制器計算調整量
    float correction = pidControl(error);

    // 根據 PID 輸出調整電機速度
    int motorSpeedLeft = 130 - correction;  // 左輪速度
    int motorSpeedRight = 130 + correction; // 右輪速度

    // 使得電機速度保持在合理範圍
    motorSpeedLeft = constrain(motorSpeedLeft, 0, 255);
    motorSpeedRight = constrain(motorSpeedRight, 0, 255);

    motor(motorSpeedLeft, 0, motorSpeedRight, 0);  // 設定左右電機速度
}

// 避開障礙物的函數
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
    // 初始化電機控制腳位
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    // 設定紅外線傳感器引腳
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);

    // 設定序列埠，便於調試
    Serial.begin(9600);
}

void loop() {
    // 測量距離
    unsigned int distance = sonar.ping_cm();
    int IR_L = digitalRead(A0);  // 左側紅外線傳感器
    int IR_R = digitalRead(A1);  // 右側紅外線傳感器
    int IR_L2 = digitalRead(A3); // 第二個左側紅外線傳感器
    int IR_R2 = digitalRead(A4); // 第二個右側紅外線傳感器

    // 輸出測量結果
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("IR_L: ");
    Serial.print(IR_L);
    Serial.print(" IR_R: ");
    Serial.println(IR_R);
    Serial.print("IR_L2: ");
    Serial.print(IR_L2);
    Serial.print(" IR_R2: ");
    Serial.println(IR_R2);
    delay(500);  // 每0.5秒更新一次

    // 如果障礙物距離小於15cm，進行避障
    if (distance <= 15) {
        obstacle_avoidance();
    } else {
        // 否則進行循跡
        line_following(IR_L, IR_R, IR_L2, IR_R2);
    }
}
