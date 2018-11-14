#include "main.h"

void testfunct();
void intake(int toggle);
void reaper(int toggle);
void flywheel(bool toggle);
void moveTo(double d);
void rightTurn(int mult);
void leftTurn(int mult);

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

	//move forward to ball in front
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);
	pros::c::delay(3000);
	intake(0);

	pros::c::delay(3000);
	//turn right 135 degrees
	rightTurn(9);
	//reaper and flywheel shoot
	flywheel(true);
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1000);

}

void auton2(){
	pros::lcd::print(0, "INIT auton2");

	//move forward to ball in front
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);
	pros::c::delay(3000);
	intake(0);

	//turn right 135 degrees
	leftTurn(9);
	//reaper and flywheel shoot
	flywheel(true);
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(1000);
}

int autonstate = 1;
std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red"};

void onCenterButton(){
//	std::string inp = "RUNNING: " + autonstateNames[autonstate - 1];
//	pros::lcd::set_text(0, inp);

	if(autonstate == 1){
		auton1();

	}
	else if(autonstate == 2){
		auton2();
	}
	else if(autonstate == 3){

	}
	else if(autonstate == 4){

	}


}

void onLeftButton(){
	if(autonstate == 4){
		autonstate = 1;
	}
	else{
		autonstate++;
	}

	std::string inp = "Selected Auton: " + autonstateNames[autonstate - 1];
	pros::lcd::set_text(0, inp);
}

void onRightButton(){
	if(autonstate == 1){
		autonstate = 4;
	}
	else{
		autonstate--;
	}

	std::string inp = "Selected Auton: " + autonstateNames[autonstate - 1];
	pros::lcd::set_text(0, inp);
}

void autonomous() {

	pros::lcd::set_text(0, "Selected Auton: none");

	pros::lcd::register_btn0_cb(onLeftButton);
	pros::lcd::register_btn1_cb(onCenterButton);
	pros::lcd::register_btn2_cb(onRightButton);


	auton2();
}
