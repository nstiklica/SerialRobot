#include <StaticThreadController.h>
#include <Thread.h>
#include "MyServo.h"

MyServo m_servo1;
MyServo m_servo2;
Thread m_syncThread;
Thread m_axisThread1;
Thread m_axisThread2;

int m_axis1_finalAngle = 0;

StaticThreadController<3> controller(&m_axisThread1, &m_axisThread2, &m_syncThread);

void setup()
{
  Serial.begin(9600);
  m_syncThread = Thread();
  m_axisThread1 = Thread();
  m_axisThread2 = Thread();

  ConfigureServos();
  ConfigureThreads();
}

void loop()
{
  controller.run();
}

void ConfigureServos()
{
  m_servo1.Init(5);
  m_servo1.SetPosition(0);

  m_servo2.Init(3);
  m_servo2.SetPosition(0);
}

void ConfigureThreads()
{
  m_axisThread1.enabled = true;
  m_axisThread1.setInterval(10);
  m_axisThread1.onRun(MoveServo1);

  m_axisThread2.enabled = true;
  m_axisThread2.setInterval(10);
  m_axisThread2.onRun(MoveServo2);

  m_syncThread.enabled = true;
  m_syncThread.setInterval(5000);
  m_syncThread.onRun(SyncFunction);
}

void MoveServo1()
{
  MoveServo(m_servo1);
}

void MoveServo2()
{
  MoveServo(m_servo2);
}

void MoveServo(MyServo servo)
{
  int currentPosition = servo.GetPosition();
  if (currentPosition == m_axis1_finalAngle)
  {
    return;
  }
  else if (currentPosition < m_axis1_finalAngle)
  {
    //  Serial.println("Increment");
    currentPosition++;
    servo.SetPosition(currentPosition);
  }
  else if (currentPosition > m_axis1_finalAngle)
  {
    currentPosition--;
    servo.SetPosition(currentPosition);
  }
}

void SyncFunction()
{
  Serial.println("SyncFunction executed");
  if (m_axis1_finalAngle == 0)
  {
    m_axis1_finalAngle = 180;
  }
  else if (m_axis1_finalAngle == 180)
  {
    m_axis1_finalAngle = 0;
  }
}
