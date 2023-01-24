#ifndef __AXIS_H__
#define __AXIS_H__

#include "MyServo.h"

class Axis
{
private:
    MyServo m_servo;

    int m_id;
    int m_finalAngle;
    int m_stepDelay;
    int m_minAngle;
    int m_maxAngle;
    int m_startPosition;
    int m_currentPosition;
    int m_step = 1;

public:
    Axis() {};

    int Init(int pinNumber, int stepDelay, int startPosition, int minAngle, int maxAngle);
    void SetAngle(int angle);
    void SetStep(int step);
    void Move();
};

#endif
