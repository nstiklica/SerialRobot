#include <StaticThreadController.h>
#include <Thread.h>

#include "Axis.h"

// MyServo m_servo1;
// MyServo m_servo2;

Axis m_axis1;
Axis m_axis2;

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
  m_axis1.Init(5, 10, 0, 0, 0);
  m_axis1.SetAngle(0);
  m_axis2.Init(3, 10, 0, 0, 0);
  m_axis2.SetAngle(0);
}

void ConfigureThreads()
{
  m_axisThread1.enabled = true;
  m_axisThread1.setInterval(10);
  m_axisThread1.onRun(Move1);

  m_axisThread2.enabled = true;
  m_axisThread2.setInterval(10);
  m_axisThread2.onRun(Move2);

  m_syncThread.enabled = true;
  m_syncThread.setInterval(3500);
  m_syncThread.onRun(SyncFunction);
}

void Move1(){
  m_axis1.Move();
}

void Move2(){
  m_axis2.Move();
}

void SyncFunction()
{
  if (m_axis1_finalAngle == 0)
  {
    m_axis1.SetAngle(180);
    m_axis2.SetAngle(180);
    m_axis1_finalAngle = 180;
  }
  else if (m_axis1_finalAngle == 180)
  {
    m_axis1.SetAngle(0);
    m_axis2.SetAngle(0);
    m_axis1_finalAngle = 0;
  }
}
