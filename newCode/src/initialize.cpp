#include "main.h"

//AUTON SELECTOR VARS//
 int autonstate = 1;
 std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red"};
 int getAutonState(){
 	return autonstate;
 }

//BUTTON CODE//
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
void onCenterButton( ){
 	std::string inp = "AUTON SELECTOR: Selected Auton: " + autonstateNames[autonstate - 1];
 	pros::lcd::set_text(0, inp);
//  autonomous();
}


void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::register_btn0_cb(onLeftButton);
	// pros::lcd::register_btn1_cb(onCenterButton);
	// pros::lcd::register_btn2_cb(onRightButton);

	// pros::lcd::set_text(0, "AUTON SELECTOR: Selected Auton: none");
}

void disabled() {} //

void competition_initialize() {} // write auton selector here
