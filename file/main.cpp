#include <arduino.h>
#include "motor.h"

// const int sensor1 = A0;
// const int sensor2 = A1;

void setup() {
    pinMode(motor1_1, OUTPUT);
    pinMode(motor1_2, OUTPUT);
    pinMode(motor2_1, OUTPUT);
    pinMode(motor2_2, OUTPUT);

    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

}

void loop() {
    int sensor_L = digitalRead(A0);
    int sensor_R = digitalRead(A1);

    if (sensor_L == 0 && sensor_R == 0) {
        run(255);
    } else if (sensor_L == 1 && sensor_R == 0) {
        motor(200, 0, 0, 0);
    } else if (sensor_L == 0 && sensor_R == 1) {
        motor(0, 0, 200, 0);
    } else {
        stop();
    }
}