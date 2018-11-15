#include "main.h"



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 int autonstate = 1;
 std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red"};


 void onLeftButton(){
 	if(autonstate == 4){
 		autonstate = 1;
 	}
 	else{
 		autonstate++;
 	}

 	std::string inp = "AUTON SELECTOR: Selected Auton: " + autonstateNames[autonstate - 1];
 	pros::lcd::set_text(0, inp);
 }
 void onRightButton(){
 	if(autonstate == 1){
 		autonstate = 4;
 	}
 	else{
 		autonstate--;
 	}
}

int getAutonState(){
	return autonstate;
}

void onCenterButton( ){
 	std::string inp = "AUTON SELECTOR: Selected Auton: " + autonstateNames[autonstate - 1];
 	pros::lcd::set_text(0, inp);
//  autonomous();
}

void initialize() {

	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(onLeftButton);
	pros::lcd::register_btn1_cb(onCenterButton);
	pros::lcd::register_btn2_cb(onRightButton);

	pros::lcd::set_text(0, "AUTON SELECTOR: Selected Auton: none");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
