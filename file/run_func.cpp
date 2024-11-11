// run_func.cpp
#include "run_func.h"  // 引入 run_func.h
#include <Arduino.h>    // 引入 Arduino 庫

// 左前 = 9
// 左後 = 10

// 右前 = 5
// 右後 = 6

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

void stop() {
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);
    analogWrite(10, 0);
}