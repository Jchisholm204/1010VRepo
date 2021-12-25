#ifndef _DRIVEBASE_HPP
#define _DRIVEBASE_HPP

#define Back -1
#define Front 1
#define Right 0
#define Left 1

#define ORIGIN_RIGHT 0
#define ORIGIN_LEFT 1

class Chassis{
public:
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
  //pid
  void pid(int targetValue, int maxSpeed, int timeout, float kP, float kD);
  //stops all drivebase movement
  void stop(void);
};

#endif
