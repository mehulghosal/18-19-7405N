#include "main.h"
#include "fps.cpp" // remove this if code no work

void handleControls();
void resetPositions();
void updatePosition();
//CONTROLLER
pros::Controller master(pros::E_CONTROLLER_MASTER);

//MOTOR INITS//
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor reaperMotor(5, pros::E_MOTOR_GEARSET_18, true);
pros::Motor flyWheelMotor(6);
pros::Motor intakeMotor(7);
pros::Motor armMotor(8);
pros::Motor motors [8] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, armMotor, reaperMotor};

//OPCONTROL DRIVE//
void chassisSet(int m1, int m2){
	backLeftMtr = m1;
	frontLeftMtr = m1;
	backRightMtr = m2;
	frontRightMtr = m2;
}

void leftTurn(double mult, int speed){ //  DEGREE INTERVALS
	resetPositions();
	int turn = (int)(mult * 8.52);
	frontRightMtr.move_absolute(turn, speed);
	backRightMtr.move_absolute(turn, speed);
	frontLeftMtr.move_absolute(-turn, -speed);
	backLeftMtr.move_absolute(-turn, -speed);
	pros::lcd::print(1,"turn: %d", turn);

	while(std::abs(frontRightMtr.get_position() - turn)>15){
		pros::c::delay(20);
	}
}

void rightTurn(double mult, int speed){
	resetPositions();
	int turn = (int)(mult * 8.54); // 128 before
	frontRightMtr.move_absolute(-turn, -speed);
	backRightMtr.move_absolute(-turn, -speed);
	backLeftMtr.move_absolute(turn, speed);
	frontLeftMtr.move_absolute(turn, speed);
	pros::lcd::print(1,"turn: %d", turn);

	while(std::abs(backLeftMtr.get_position() - turn)>15){
		pros::c::delay(20);
	}
}

void drive(int driveL, int driveR) {

	if(abs(driveL) >= 15 || abs(driveR) >= 15) {
		chassisSet(std::min(std::max(driveL + driveR, -127),127), std::min(std::max(driveL - driveR, -127),127));
	}
	else {
		chassisSet(0,0);
	}
	pros::lcd::print(3, "BL: %d FL: %d", (backLeftMtr.get_actual_velocity()),(frontLeftMtr.get_actual_velocity()));
	pros::lcd::print(4, "BR: %d FR: %d", (backRightMtr.get_actual_velocity()),(frontRightMtr.get_actual_velocity()));

}

//OTHER CONTROLS//
void flywheel(bool toggle){
	if(toggle){
		flyWheelMotor = 127;
	}
	else {
		flyWheelMotor = 0;
	}
}
void reaper(int toggle){
	if(toggle == 1){
		reaperMotor = 127;
	}
	else if(toggle == 0){
		reaperMotor = 0;
	}
	else {
		reaperMotor = -127;
	}
}

void moveReaper(int dist, bool delay){
	reaperMotor.move_relative(dist, 150);

	if(delay){
		while(std::abs(reaperMotor.get_position() - dist)>15){
			pros::c::delay(10);
		}
	}
}
void intake(int toggle){
	if(toggle == 1){
		intakeMotor = 127;
	}
	if(toggle == -1){
		intakeMotor = -127;
	}
	if(toggle == 0){
		intakeMotor = 0;
	}
}
void arm(bool toggle){
	if(toggle == true){
		armMotor.move_absolute(100, 100);
		armMotor = 15;
	}
	else{
		armMotor.move_absolute(-100, 100);
		armMotor = -15;
	}
}

//AUTON CONTROLS//

void moveTo(double d){
	resetPositions();
	int speedCoef = 1;
	if(d<0){speedCoef = -1;}
	frontLeftMtr.move_absolute(d, speedCoef*150);
	frontRightMtr.move_absolute(d, speedCoef*150);
	backLeftMtr.move_absolute(d, speedCoef*150);
	backRightMtr.move_absolute(d, speedCoef*150);
	pros::lcd::print(1,"move: %d", d);

	while(std::abs(backLeftMtr.get_position() - d)>15){
		pros::c::delay(10);
	}
}

//pid - work with this l8r
//todo: do the thing josh was talkign about with tracking velocties
//if velo < some value: turn off all motors, but also make sure time is greater than 100
//also incorporate chasiset for turning
void moveTo1(double d){
	resetPositions();
	double diff = (d - frontLeftMtr.get_position());
	//coeff
	double q = .1;

	int time = pros::millis();

	while(diff > 5 && (frontLeftMtr.get_actual_velocity() > 20  || pros::millis() - time > 100)){
		pros::lcd::print(1, "diff: %d", diff);
		diff = (d - frontLeftMtr.get_position());
		chassisSet(diff * q, diff * q);

	}
	chassisSet(0, 0);
}


void resetPositions(){
	backRightMtr.tare_position();
	backLeftMtr.tare_position();
	frontLeftMtr.tare_position();
	frontRightMtr.tare_position();
}

//MISC CONTROLS//
void motorStop() {
	for (int i = 0; i < 8; i++) {
		motors[i] = 0;
	}
}
void testfunct(){
	//FOR TESTING CODE//
}

void opcontrol() {

	//fuck this all jeez
	//testfunct();
	int prevTravelDist = 0;
	bool flyWheelToggle = false;
	int intakeToggle = 0;
	int reaperToggle = 0;
	bool xPressed = false;
	bool yPressed = false;
	bool left = false;
	bool right = false;
	bool bPressed = false;
	bool lPressed = false;
	bool rPressed = false;

	while (true) {

		handleControls(); // this function handles all the controls cause i never want to look at them again - i feel
		int driveLeft = master.get_analog(ANALOG_LEFT_Y);
		int driveRight = master.get_analog(ANALOG_RIGHT_X);
		int angleOfBot = 0;

		updatePosition((frontLeftMtr.get_position() - prevTravelDist), angleOfBot);
		
		prevTravelDist = frontLeftMtr.get_position()

		pros::lcd::print(1, "Reaper: %f Intake: %d", (reaperMotor.get_actual_velocity()),(int)intakeToggle);
		pros::lcd::print(2, "Flywheel: %f", (flyWheelMotor.get_actual_velocity()));

		pros::Task::delay(20);

	}
}

//god this makes me barf but ig its warranted
void handleControls(){

	pros::ADIDigitalIn limit ('A');

	


	if (master.get_digital(DIGITAL_X) == 1 && xPressed == false){
		if(limit.get_value() == 1 && reaperToggle == 1){
			reaperToggle = 0;
		}
		else if (limit.get_value() == 1 && reaperToggle == 0){
			reaperToggle = 1;
		}
		else if (reaperToggle == 0 || reaperToggle == -1){
			reaperToggle = 1;
		}
		else if(reaperToggle == 1){
			reaperToggle = 0;
		}
		xPressed = true;
	}
	else if(master.get_digital(DIGITAL_X) == 0) {
		if(limit.get_value() == 1 && reaperToggle == 1){
			reaperToggle = 0;
		}
		else if (limit.get_value() == 1 && reaperToggle == 0){
			reaperToggle = 0;
		}
		xPressed = false;
	}



	if (master.get_digital(DIGITAL_B) == 1 && bPressed == false) {
		if (reaperToggle == -1){
			reaperToggle = 0;
		}
		else if (reaperToggle == 0 || reaperToggle == 1){
			reaperToggle = -1;
		}
		bPressed = true;


	}
	else if (master.get_digital(DIGITAL_B) == 0) {
		bPressed = false;
	}

	//intake toggling
	if (master.get_digital(DIGITAL_LEFT) == 1 && lPressed == false ){

		if (intakeToggle == 1){
			intakeToggle = 0;
		}
		else if (intakeToggle == 0 || intakeToggle == -1){
			intakeToggle = 1;
		}
		lPressed = true;

	}
	else if (master.get_digital(DIGITAL_LEFT) == 0){
		lPressed = false;
	}

	if (master.get_digital(DIGITAL_RIGHT) == 1 && rPressed == false) {

		if (intakeToggle == -1){
			intakeToggle = 0;
		}
		else if (intakeToggle == 0 || intakeToggle == 1){
			intakeToggle = -1;
		}
		rPressed = true;

	}
	else if (master.get_digital(DIGITAL_RIGHT) == 0){
		rPressed = false;
	}

	//flywheel toggling
	if (master.get_digital(DIGITAL_Y) == 1 && yPressed == false){
		flyWheelToggle = !flyWheelToggle;
		yPressed = true;
		pros::Task::delay(20);
	}
	else if (master.get_digital(DIGITAL_Y) == 0){
		yPressed = false;
	}

	// pros::lcd::print(2, "ARM: %d",(int)armMotor.get_position()) ;
	if(master.get_digital(DIGITAL_R2) == 1){
			armMotor = 100;
	}
	else if(master.get_digital(DIGITAL_L2) == 1){
			armMotor = -100;
	}
	else if(armMotor.get_position() >= 400){
		armMotor = -15;
	}

	else if(armMotor.get_position() < 400){
		armMotor = 15;
	}

	if (master.get_digital(DIGITAL_UP) == 1) {
		motorStop();
	}
	intake(intakeToggle);
	flywheel(flyWheelToggle);
	drive(driveLeft, driveRight);
	reaper(reaperToggle);
}
