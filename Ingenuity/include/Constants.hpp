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
    constexpr int LIFT_PISTON = 0;
    constexpr int DOCK_PISTON = 0;


    //#SENSORS#

    // Lift Potentiometer; Used to get Absolute Positioning control on the Lift Appratus
    constexpr int Lift_Potentiometer = 0;

    // Gyro should be installed somewhere close to the center of the robot
    constexpr int Gyro = 0; // (1-21)

    //#MOTORS#
    // Drive Right Back
    constexpr int driveRB = 0;
    // Drive Right Middle
    constexpr int driveRM = 0;
    // Drive Right Front
    constexpr int driveRF = 9;

    // Drive Left Back
    constexpr int driveLB = 0;
    // Drive Left Middle
    constexpr int driveLM = 0;
    // Drive Left Front
    constexpr int driveLF = 0;

    // Conveyor Motor Port
    constexpr int CONVEYER = 0;

    // Lift Motor Port
    constexpr int LIFT = 0;
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
    constexpr int TargetValue_Down = 3900;
    // Slightly lower than all the way up (useful for putting mogos on platform)
    constexpr int TargetValue_MidWay = 3000;
    // All the Way Up (clears platform)
    constexpr int TargetValue_Up = 580;

    // Lift Porportional Gain
    constexpr float kP = 1.8;
    // Lift Derivitive Gain
    constexpr float kD = 0.8;

    // Lift PD Maximum Velocity
    constexpr int Maximum_Velocity = 100;

} // namespace kLift


#endif