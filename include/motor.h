#ifndef MOTOR_H
#define MOTOR_H

void run(int speed);
void back(int speed);
void left(int speed);
void right(int speed);
void back_left(int speed);
void back_right(int speed);
void stop();
void motor(int leftForward, int leftBackward, int rightForward, int rightBackward);

#endif