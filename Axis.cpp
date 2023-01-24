#include "Axis.h"

int Axis::Init(int pinNumber, int stepDelay, int startPosition, int minAngle, int maxAngle)
{
    m_servo.Init(pinNumber);
    m_stepDelay = stepDelay;
    m_startPosition = startPosition;
    m_minAngle = minAngle;
    m_maxAngle = maxAngle;
}

void Axis::SetAngle(int angle)
{
    m_finalAngle = angle;
}

void Axis::SetStep(int step)
{
    m_step = step;
}

void Axis::Move()
{
    int currentPosition = m_servo.GetPosition();

    if (currentPosition == m_finalAngle)
    {
        return;
    }
    else if (currentPosition < m_finalAngle)
    {
        currentPosition++;
        m_servo.SetPosition(currentPosition);
    }
    else if (currentPosition > m_finalAngle)
    {
        currentPosition--;
        m_servo.SetPosition(currentPosition);
    }
}
