#include "main.h"
#include "constants.h"

//AUTON SELECTOR VARS//
 int autonstate = 1;
 bool ParkState = true;
int targSpeed = 200;



 std::string autonstateNames[] = {"top blue", "top red", "back blue", "back red", "codeSkills"};
 int getAutonState(){
 	return autonstate;
 }
bool getParkState()
{
  return ParkState;
}
//BUTTON CODE//
 void onLeftButton(){
 	if(autonstate == 5){
 		autonstate = 1;
 	}
 	else{
 		autonstate++;
 	}
 	std::string inp = "AUTON SELECTOR: Selected Auton: " + autonstateNames[autonstate - 1];
 	pros::lcd::set_text(0, inp);
 }
 void onRightButton(){
 	if(ParkState)
  {
    ParkState = false;
  }
  else {
    ParkState = true;
  }

 	pros::lcd::print(6, "ParkState: %d", ParkState);
}
void onCenterButton( ){
 	std::string inp = "RUNNING AUTON: " + autonstateNames[autonstate - 1];
 	pros::lcd::set_text(0, inp);
  pros::c::delay(3000);
}




void initialize() {


	pros::lcd::initialize();
	pros::lcd::register_btn0_cb(onLeftButton);
	pros::lcd::register_btn1_cb(onCenterButton);
	pros::lcd::register_btn2_cb(onRightButton);





	pros::lcd::set_text(0, "AUTON SELECTOR: Selected Auton: none");
}

void disabled() {} //

void competition_initialize() {} // write auton selector here
