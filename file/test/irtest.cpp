#include <Arduino.h>
#include <NewPing.h>

const int trigPin = 11;
const int echoPin = 12;
const int MAX_DISTANCE = 200; // 最大測量距離（單位：厘米）
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

    Serial.begin(9600);
}

void loop() {
    unsigned int distance = sonar.ping_cm();

    int IR_L = digitalRead(A0);
    int IR_R = digitalRead(A1);
    int IR_L2 = digitalRead(A3);

    Serial.print("IR_L: ");
    Serial.println(IR_L);

    Serial.print("IR_R: ");
    Serial.println(IR_R);

    Serial.print("IR_L2: ");
    Serial.println(IR_L2);

    Serial.print("cm: ");
    Serial.println(distance);

    delay(500);
}