#ifndef MOTOR_H
#define MOTOR_H

const int motor1_1 = 5;
const int motor1_2 = 6;
const int motor2_1 = 9;
const int motor2_2 = 10;

void run(int speed);
void back(int speed);
void left(int speed);
void right(int speed);
void stop();

#endif
