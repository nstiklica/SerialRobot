#include "MyServo.h"

MyServo::MyServo() {}

MyServo::Init(int pinNumber)
{
    m_servo.attach(pinNumber);
}

void MyServo::SetPosition(int pos)
{
    m_servo.write(pos);
}

int MyServo::GetPosition()
{
    return m_servo.read();
}
