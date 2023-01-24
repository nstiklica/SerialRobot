#ifndef __MYSERVO_H__
#define __MYSERVO_H__

#include <Servo.h>

class MyServo
{
    private:
        Servo m_servo;

    public:
        MyServo();
        Init(int pinNumber);

        void SetPosition(int pos);
        int GetPosition();
};

#endif
