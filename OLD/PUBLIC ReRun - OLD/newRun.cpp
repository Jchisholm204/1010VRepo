#include "main.h"
#include "run.h"

void Run() {
  //
  FILE *fp;

  fp = fopen("/usd/example.txt", "r");
  float lastTime = 0;
  static float m1, m2; //these are placeholders for motor velocities

  //Main while loop
  while (true) {
//reading from the array
    fscanf(fp, "%f""%f", &m1, &m2);
    printf("%f\n", m1);
//moving motors using array values
  testMotor.move_voltage(m1);
  testMotor2.move_voltage(m2);
  lastTime = millis(); // updates the lastTime is program was run
  delay(10);
}
}
