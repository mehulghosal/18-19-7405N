#include "main.h"

void testfunct();
void intake(int toggle);
void moveTo(double d, double RC, double LC); 

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

//blue on the top
void auton1(){
	pros::lcd::print(0, "INIT auton1");
	//pros::c::delay(2000);

	//testfunct();
	//move forward to ball in front
	moveTo(400, 0, 0);//i have no idea what this magnitude should be

	//turn on intake
	intake(1);
	pros::c::delay(1000);
	intake(0);

	//turn right - how the heck
	//moveTo();

	//reaper and flywheel shoot
}

void autonomous() {
	auton1();
}
