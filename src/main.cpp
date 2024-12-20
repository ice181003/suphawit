/*
#include <Arduino.h>
int ledPin = 23; // GPIOC13 (PWM Channel 8)

void setup() {
pinMode(ledPin, OUTPUT); // Set GPIOC13 as Output
analogWrite(ledPin, 0); // Set PWM Channel 8
}

void loop() {
for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
analogWrite(ledPin, dutyCycle);
delay(10);
}

for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
analogWrite(ledPin, dutyCycle);
delay(10);
}
}
*/