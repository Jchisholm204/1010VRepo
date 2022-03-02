//Ingenuity - Constants.hpp
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

/** Ingenuity - Constants.hpp
 * 
 * @author Jchisholm
 * #Team 1010V
 * 
 * Constants File:
 *      Contains all of the Robot contants: Ports, TargetValues, ext..
 */


/** kPorts:
 * 
 * kPorts Contains all of the constant expressions for all of the Physical ports on the Robot
 * 
 * These constants are used when initializing any physical motor, sensor or other device on the robot.
 * 
 * They are declared here as constants because motors and sensors are declared throughought the code within their subsystems,
 * Having them here makes it easy to change all of the ports from one central place.
 */
namespace kPorts {

    //pnumatic controllers
    constexpr int LIFT_PISTON = 0; // ( 1 - 8 ) NOT (A - H)
    constexpr int DOCK_PISTON = 0; // ( 1 - 8 ) NOT (A - H)


    //#SENSORS#

    // Lift Potentiometer; Used to get Absolute Positioning control on the Lift Appratus
    constexpr int Lift_Potentiometer = 21;

    // Gyro should be installed somewhere close to the center of the robot
    constexpr int Gyro = 0; // (1-21)

    //#MOTORS#
    // Drive Right Back
    constexpr int driveRB = 0; // (1-21)
    // Drive Right Middle
    constexpr int driveRM = 0; // (1-21)
    // Drive Right Front
    constexpr int driveRF = 9; // (1-21)

    // Drive Left Back
    constexpr int driveLB = 0; // (1-21)
    // Drive Left Middle
    constexpr int driveLM = 0; // (1-21)
    // Drive Left Front
    constexpr int driveLF = 0; // (1-21)

    // Conveyor Motor Port
    constexpr int CONVEYER = 0; // (1-21)

    // Lift Motor Port
    constexpr int LIFT = 20; // (1-21)
    
} // namespace kPorts


/** kLift:
 * 
 * Contains:
 * 
 * All of the Constants used in both the initialization and running of the Lift Apparatus.
 * This includes lift kD and kP, as well as targetvalues for the lift positions
 */
namespace kLift {
    
    // When the Lift is At the Very Bottom
    constexpr int TargetValue_Down = 4;
    // Slightly lower than all the way up (useful for putting mogos on platform)
    constexpr int TargetValue_MidWay = 55;
    // All the Way Up (clears platform)
    constexpr int TargetValue_Up = 105;

    // Lift Porportional Gain (High Draw)
    constexpr float kP = 6.3;
    // Lift Derivitive Gain (High Draw)
    constexpr float kD = 0.8;

    // Lift Porportional Gain (Low Draw)
    constexpr float klP = 2.2;
    // Lift Derivitive Gain (Low Draw)
    constexpr float klD = 0.4;
    

    // Lift PD Maximum Velocity
    constexpr int Maximum_Velocity = 100;

    // Lift Motor Wattage Threshold for Switching P and D constants
    constexpr double W_Threshold = 3.6;

} // namespace kLift

/** kOperator
 * Operator Control Constants
 */
namespace kOperator {
    // The Maximum DriveBase Velocity for Operator Control (out of 200)
    constexpr int MaximumDrive_Velocity = 200;
    // The Slow Drive Velocity (used for climbing, also out of 200)
    constexpr int SlowDrive_Velocity = 70;

    // The Manual Lift Velocity (maximum of 100)
    constexpr int Lift_Velocity = 100;
}


#endif