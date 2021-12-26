#ifndef _DRIVEBASE_HPP
#define _DRIVEBASE_HPP

#define Back -1
#define Front 1
#define Right 0
#define Left 1

#define ORIGIN_RIGHT 0
#define ORIGIN_LEFT 1

//Drive_PID List Macros

#define drive_kP 0
#define drive_kD 1
#define drive_max_power 2

//Drive Distance Sources

#define ENCODERS 0
//Distance Sensors on the Front of the Robot
#define Front_Distance 1
//Distance Sensors on the Back of the Robot
#define Back_Distance 2


class Chassis{
public:

  /**
   * @brief Construct a new Chassis object
   * 
   * @param maxVal Maximum Drive Power
   * @param nkP Drive kP
   * @param nkD drive kD
   */
  Chassis(float maxVal, float nkP, float nkD);

  //exponential drive function
  int exponential(int joystickVal, float driveExp, int joydead, int motorMin);

  /**
   * @brief Operator Chassis using Arcade Drive With Expo
   * 
   * @param maxVel The Maximum Velocity The Drivebase Can Run (0-200)
   */
  void operator_Chassis(int maxVel);

  /**
   * @brief Time Driven Drivebase Movement with Different Drive Velocities
   * 
   * @param time The Time To Drive For
   * @param leftPow The Velocity of The Left Side of The Robot
   * @param rightPow The Velocity of The Right Side of The Robot
   */
  void time(int time, int leftPow, int rightPow);
  /**
   * @brief Time Driven Drivebase Movement
   * 
   * @param time The Time To Drive For
   * @param velocity The Velocity of All 4 drive motors
   */
  void time(int time, int velocity);
  /**
   * @brief Encoder Based Drivebase Movement With Left and Right PID Values
   * 
   * @param leftTarget The Left Side PID Target
   * @param maxLeft The Maximum Power (Speed) That Can be Applied to the Left Side
   * @param rightTarget The Right Side PID Target
   * @param maxRight The Maximum Power (Speed) That Can be Applied to the Right Side
   * @param timeout The PID Timeout in ms
   */
  void driveTurn(int leftTarget, int maxLeft, int rightTarget, int maxRight, int timeout);
  
  /**
   * @brief Gyro Based Drivebase Turning with Center Origins
   * 
   * @param targetValue The Degrees to Turn from its Current Position
   * @param timeout The PID Timeout in ms
   */
  void turn(int targetValue, int timeout);

  /**
   * @brief Adjust DriveBase PID Values
   * 
   * @param MaxPower Maximum Power that can be applied to the drivebase
   * @param kP Drive kP
   * @param kD Drive kD
   */
  void adj_pid(float MaxPower, float nkP, float nkD);

  //Encoder Movement
  void drive(int targetValue, int maxSpeed, int timeout);

  void distance(int source, int targetValue, int timeout);

  //stops all drivebase movement
  void stop(void);

  //resets drive motor encoders
  void reset(void);

  //Stores Drive PID Values
  float drive_PID[2];
};

#endif
