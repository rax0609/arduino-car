#include <Arduino.h>
#include <NewPing.h>    // 引入 NewPing 庫

// 定義馬達引腳
const int motor1_1 = 9;
const int motor1_2 = 10;

const int motor2_1 = 5;
const int motor2_2 = 6;

// 定義超音波感測器引腳和最大距離
const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）

// 創建 NewPing 物件
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// 定義 IR 感測器引腳
int IR_L = digitalRead(A0);
int IR_R = digitalRead(A1);

// run 函數，控制馬達的速度
void run(int speed) {
    analogWrite(5, speed);
    analogWrite(6, 0);
    analogWrite(9, speed);
    analogWrite(10, 0);
}

// left 函數，控制馬達左轉特定的角度
void left(int speed) {
    analogWrite(5, speed);  // 右前馬達正轉
    analogWrite(6, 0);      // 右後馬達停止
    analogWrite(9, 0);      // 左前馬達停止
    analogWrite(10, speed); // 左後馬達反轉
}

void right(int speed) {
    analogWrite(5, 0);
    analogWrite(6, speed);
    analogWrite(9, speed);
    analogWrite(10, 0);
}

void stop() {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}

void setup() {
    // 設置 PWM 引腳模式（motor1_1 和 motor2_1 用於控制馬達）
    pinMode(motor1_1, OUTPUT);
    pinMode(motor1_2, OUTPUT);
    pinMode(motor2_1, OUTPUT);
    pinMode(motor2_2, OUTPUT);

    // 初始化串列通訊
    Serial.begin(9600);
}

void line_following() {
    if (IR_L == 0 && IR_R == 0) {
        run(180);
    }
}

void loop() {
    // 使用 NewPing 庫測量距離
    unsigned int distance = sonar.ping_cm();
    // 在串列監視器上顯示距離
    Serial.print("距離: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);

    if (distance < 10) {
        run(180);
    } else {
        stop();
    }
}