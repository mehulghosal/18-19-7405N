#include "main.h"
#include "opcontrol.cpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */


void autonomous(){
	auton1();
}

//top blue
void auton1(){
	pros::lcd::print(0, "auton1 init");
	moveTo(25, 0, 0);

}

//bottom blue
void auton2(){

}

//top red
void auton3(){

}

//bottom red
void auton4(){

}
