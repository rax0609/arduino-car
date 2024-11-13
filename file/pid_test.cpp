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

// PID參數
float Kp = 0.5;  // 比例常數
float Ki = 0.1;  // 積分常數
float Kd = 0.2;  // 微分常數

float previousError = 0; // 前一個誤差
float integral = 0;      // 積分項

// run 函數，控制馬達前進
void run(int speed) {
    analogWrite(motor2_1, speed);
    analogWrite(motor2_2, 0);
    analogWrite(motor1_1, speed);
    analogWrite(motor1_2, 0);
}

// back 函數，控制馬達倒車
void back(int speed) {
    analogWrite(motor2_1, 0);
    analogWrite(motor2_2, speed);
    analogWrite(motor1_1, 0);
    analogWrite(motor1_2, speed);
}

// left 函數，控制馬達左轉特定的角度
void left(int speed) {
    analogWrite(motor2_1, speed);  // 右前馬達正轉
    analogWrite(motor2_2, 0);      // 右後馬達停止
    analogWrite(motor1_1, 0);      // 左前馬達停止
    analogWrite(motor1_2, speed); // 左後馬達反轉
}

void right(int speed) {
    analogWrite(motor2_1, 0);
    analogWrite(motor2_2, speed);
    analogWrite(motor1_1, speed);
    analogWrite(motor1_2, 0);
}

void move(int speed1, int speed2, int speed3, int speed4) {
    analogWrite(motor1_1, speed1);
    analogWrite(motor1_2, speed2);
    analogWrite(motor2_1, speed3);
    analogWrite(motor2_2, speed4);
}

// 停止函數
void stop() {
    analogWrite(motor2_1, 0);
    analogWrite(motor2_2, 0);
    analogWrite(motor1_1, 0);
    analogWrite(motor1_2, 0);
}

// PID計算函數
float calculatePID(float error) {
    integral += error;  // 積分
    
    // 限制積分項的範圍，防止過多累積
    if (integral > 100) integral = 100;
    if (integral < -100) integral = -100;

    float derivative = error - previousError;  // 微分
    float output = Kp * error + Ki * integral + Kd * derivative;  // PID公式
    previousError = error;  // 更新前一個誤差
    return output;
}


// 循線PID函數
void line_following() {
    // 計算誤差（左右感測器的偏差）
    float error = IR_L - IR_R;  // 假設當IR_L和IR_R的值相等時，車輛在黑線上

    // 計算PID輸出
    float output = calculatePID(error);

    // 根據PID輸出調整馬達速度
    int speed = 180;  // 預設速度

    // 如果偏離太遠，減速並進行修正
    if (abs(output) > 50) {
        speed = 120;  // 偏離黑線過多，減速
    }

    if (output > 0) {
        move(0, 0, speed, 0);
    } else if (output < 0) {
        move(speed, 0, 0, 0);
    } else {
        run(speed);  // 沒有誤差時直行
    }
}

void obstacle_avoidance() {
    unsigned int distance = sonar.ping_cm();

    // 確保距離值有效
    if (distance == 0) {
        return;  // 如果距離無效，則退出
    }

    // 如果距離小於10cm，則觸發避障
    if (distance <= 10) {
        // 計算避障PID控制
        float error = 10 - distance;  // 假設目標距離是10cm
        float output = calculatePID(error);

        // 根據PID調整行為（後退或轉向）
        int speed = 150; // 避障時減速

        if (output > 0) {
            back(speed);  // 後退
        } else if (output < 0) {
            left(speed);  // 左轉
        } else {
            right(speed);  // 右轉
        }
    } else {
        line_following();  // 沒有障礙物時繼續循線
    }
}


void setup() {
    // 設置 PWM 引腳模式（motor1_1 和 motor2_1 用於控制馬達）
    pinMode(motor1_1, OUTPUT);
    pinMode(motor1_2, OUTPUT);
    pinMode(motor2_1, OUTPUT);
    pinMode(motor2_2, OUTPUT);

    // 設置 IR 感測器為輸入模式
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    // 初始化串列通訊
    Serial.begin(9600);
}


void loop() {
    // 更新IR感測器值
    IR_L = digitalRead(A0);
    IR_R = digitalRead(A1);

    // 使用 NewPing 庫測量距離
    unsigned int distance = sonar.ping_cm();

    // 在串列監視器上顯示距離
    Serial.print("距離: ");
    Serial.print(distance);
    Serial.println(" cm");

    // 顯示 IR 感測器狀態
    Serial.print("IR_L: ");
    Serial.print(IR_L);
    Serial.print(" IR_R: ");
    Serial.println(IR_R);
    delay(1000);

    // 先進行避障，再進行循線
    obstacle_avoidance();
}