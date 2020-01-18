#define trigPin A0      //Assin PIN A0 as trigPin (Connect ARDUINO UNO "A0" pin with Ultrasonic Sonar Sensor "TRIG" Pin)
#define echoPin A1      //Assin PIN A1 as echoPin (Connect ARDUINO UNO "A1" pin with Ultrasonic Sonar Sensor "ECHO" Pin)

#define MotorA_IN1 3      //Assin PIN 3 as MotorA_IN1 (Connect ARDUINO UNO "3" pin with L293D Motor Driver "IN1" Pin)
#define MotorA_IN2 4      //Assin PIN 4 as MotorA_IN2 (Connect ARDUINO UNO "4" pin with L293D Motor Driver "IN2" Pin)

#define MotorB_IN3 5      //Assin PIN 5 as MotorB_IN3 (Connect ARDUINO UNO "5" pin with L293D Motor Driver "IN3" Pin)
#define MotorB_IN4 6      //Assin PIN 6 as MotorB_IN4 (Connect ARDUINO UNO "6" pin with L293D Motor Driver "IN4" Pin)

#define MotorA_PWM 9      //Assin PIN 9 as MotorA_PWM (Connect ARDUINO UNO "9" pin with L293D Motor Driver "ENA" Pin)
#define MotorB_PWM 10     //Assin PIN 10 as MotorB_PWM (Connect ARDUINO UNO "10" pin with L293D Motor Driver "ENB" Pin)

void setup() {
  pinMode(MotorA_IN1, OUTPUT);      //Declare "MotorA_IN1" as "Output Pin".
  pinMode(MotorA_IN2, OUTPUT);      //Declare "MotorA_IN2" as "Output Pin".

  pinMode(MotorB_IN3, OUTPUT);      //Declare "MotorB_IN3" as "Output Pin".
  pinMode(MotorB_IN4, OUTPUT);      //Declare "MotorB_IN4" as "Output Pin".

  pinMode(MotorA_PWM, OUTPUT);      //Declare "MotorA_PWM" as "Output Pin".
  pinMode(MotorB_PWM, OUTPUT);      //Declare "MotorA_PWM" as "Output Pin".

  pinMode(trigPin, OUTPUT);      //Declare "trigPin" as "Output Pin".
  pinMode(echoPin, INPUT);      //Declare "echoPin" as "Input Pin".
}

int search(void)
{
  float duration = 0.00;      //Float type variable declaration
  float CM = 0.00;

  digitalWrite(trigPin, LOW);     //Trig_pin uotput as 0V (Logic Low-Level)
  delayMicroseconds(2);     //Delay for 2 us

  //Send 10us High Pulse to Ultra-sonic Sonar Sensor "trigpin"
  digitalWrite(trigPin, HIGH);      //Trig-pin output as 5V (Logic High-Level)
  delayMicroseconds(10);     //Delay for 10 us

  digitalWrite(trigPin, LOW);     //Trig_pin uotput as 0V (Logic Low-Level)

  duration = pulseIn(echoPin, HIGH);      //Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration"

  CM = (duration / 58.82);    //Convert distance into CM.

  return CM;
}

void loop() {
  float distance = 0.00;
  float RobotSpeed = 0.00;


  //Measuring the distance in CM
  distance = search();

  if ((distance < 40))    //If obstaclw found in 40 CM.
  {
    RobotSpeed = 100;     //Speed Down

    analogWrite(MotorA_PWM, RobotSpeed);      //Update speed in MOTORA Output Terminal
    analogWrite(MotorB_PWM, RobotSpeed);      //Update speed in MOTORB Output Terminal

    RobotStop();      //Robot Stop
    delay(10);

    RobotBackward();      //Robot Run Backward Direction
    delay(400);

    RobotStop();      //Robot Stop
    delay(10);

    distance = search();      //Check obstacle again

    int a = 250;
    int b = 250;

    if (distance < 30)  //30cm
    {
      RobotRight();     //Robot Turn into Right Direction
      a = a + 50;
      delay(a);

      distance = search();      //Check obstacle again
    }
    else
    {
      b = b + 50;
      RobotLeft();     //Robot Turn into Left Direction
      delay(b);

      distance = search();      //Check obstacle again
    }

  }
  else if ((distance >= 40) && (distance <= 70))
  {
    RobotSpeed = 150;     //Speed Increase Slightly

    analogWrite(MotorA_PWM, RobotSpeed);      //Update speed in MOTORA Output Terminal
    analogWrite(MotorB_PWM, RobotSpeed);      //Update speed in MOTORB Output Terminal


    RobotBackward();
  }

  else
  {
    RobotSpeed = 255;     //Speed increase to full speed

    analogWrite(MotorA_PWM, RobotSpeed);      //Update speed in MOTORA Output Terminal
    analogWrite(MotorB_PWM, RobotSpeed);      //Update speed in MOTORB Output Terminal

    RobotForward();      //Robot Move to Forward Direction
  }

}

void RobotForward()
{
  digitalWrite(MotorA_IN1, HIGH);
  digitalWrite(MotorA_IN2, LOW);
  digitalWrite(MotorB_IN3, HIGH);
  digitalWrite(MotorB_IN4, LOW);
}

void RobotBackward()
{
  digitalWrite(MotorA_IN1, LOW);
  digitalWrite(MotorA_IN2, HIGH);
  digitalWrite(MotorB_IN3, LOW);
  digitalWrite(MotorB_IN4, HIGH);
}

void RobotLeft()
{
  digitalWrite(MotorA_IN1, LOW);
  digitalWrite(MotorA_IN2, HIGH);
  digitalWrite(MotorB_IN3, HIGH);
  digitalWrite(MotorB_IN4, LOW);
}

void RobotRight()
{
  digitalWrite(MotorA_IN1, HIGH);
  digitalWrite(MotorA_IN2, LOW);
  digitalWrite(MotorB_IN3, LOW);
  digitalWrite(MotorB_IN4, HIGH);
}

void RobotStop()
{
  digitalWrite(MotorA_IN1, LOW);
  digitalWrite(MotorA_IN2, LOW);
  digitalWrite(MotorB_IN3, LOW);
  digitalWrite(MotorB_IN4, LOW);
}
