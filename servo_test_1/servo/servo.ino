#include <HCSR04.h>
#include <Servo.h>

const int triggerPin = 13; 
const int echoPin = 12;
const int servoPin = 2;
UltraSonicDistanceSensor radar(triggerPin, echoPin);

Servo servo;
const int max_angle = 180;

void setup() {
  // Initialize the Serial port, which we'll use to send out data
  // in the form <angle, distance>
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
}

inline
void measure_and_print(int angle) {
  double distance = 0.0;
  double curr_measurement;
  const int iter = 5;
  for (int i = 0; i < iter; ++i) {
    curr_measurement = radar.measureDistanceCm();
    distance += (curr_measurement / iter);
    
    #ifndef NDEBUG
    Serial.print(angle);
    Serial.print(" ");
    Serial.println(curr_measurement);
    #endif
  }
  // Print out the average distance
  Serial.println(distance);
}

inline 
void swipe(int init, int end, int angle_inc, int dtime, int measure_period = 20) {
  // Setup the variables so that the fix for loop we have below causes the
  // servo to rotate in the right direction.
  int* angle = &init;
  if (init > end) {
    angle_inc = -abs(angle_inc);
  } else {
    angle_inc = abs(angle_inc);
    // Swap the values of init and end, so that the for loop works
    int aux = end;
    end = init;
    init = aux;
  }

  for (; init >= end; *angle += angle_inc) {
      if (*angle % measure_period == 0) {
        measure_and_print(*angle);
      }
      servo.write(*angle);
      delay(dtime);    
  }
}

void loop() {
  const int angle_inc = 5;
  const int dtime = 100;
  delay(200);
  
  while (true) {
    const int sample_period = 10;
    swipe(0, max_angle, angle_inc, dtime, sample_period);
    swipe(max_angle, 0, angle_inc, dtime, sample_period);
  }
}
