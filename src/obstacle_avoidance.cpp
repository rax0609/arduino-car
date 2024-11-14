#include <Arduino.h>
#include <NewPing.h>
#include "motor.h"

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    unsigned int distance = sonar.ping_cm();

    if (distance <= 15) {
        delay(1000);
        stop();
        back(180);
        left(130);
    } else {
        run(255);
    }
}