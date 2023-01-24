#include <StaticThreadController.h>
#include <Thread.h>
#include <Servo.h>

Servo m_servo;
Servo m_servo2;
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

  m_servo.attach(5);
  m_servo.write(0);

  m_servo2.attach(3);
  m_servo2.write(0);

  ConfigureThreads();
}

void loop()
{
  controller.run();
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

void MoveServo1(){
  MoveServo(m_servo);
}

void MoveServo2(){
  MoveServo(m_servo2);
}

void MoveServo(Servo servo){
    int currentPosition = servo.read();
  if (currentPosition == m_axis1_finalAngle)
  {
    return;
  }
  else if (currentPosition < m_axis1_finalAngle)
  {
  //  Serial.println("Increment");
    currentPosition++;
    servo.write(currentPosition);
  }
  else if (currentPosition > m_axis1_finalAngle)
  {
    currentPosition--;
    servo.write(currentPosition);
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
