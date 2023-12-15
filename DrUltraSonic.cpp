#include "DrUltraSonic.h"
#include <M5Stack.h>
#include "M5All-In-One-Gadget.h"

DrUltraSonic::DrUltraSonic(int echo_pin, int trig_pin)
{

    m_echo_pin = echo_pin;
    m_trig_pin = trig_pin;
    pinMode(m_echo_pin, INPUT);
    pinMode(m_trig_pin, OUTPUT);
}

double DrUltraSonic::measureReturnTime()
{
    double t;
    double distance = 0;
    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);

    t = pulseIn(ECHO_PIN, HIGH);
    Serial.println(t);
    return t;
}
