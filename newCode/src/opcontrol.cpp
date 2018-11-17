#include "main.h"

//void leftTurn();
void resetPositions();
void rightTurn();

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
		reaperMotor = 80;
	}
	else if(toggle == 0){
		reaperMotor = 0;
	}
	else {
		reaperMotor = -80;
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
	}
	else{
		armMotor.move_absolute(-100, 100);
	}
}

//AUTON CONTROLS//
void moveTo(double d){    
	resetPositions();
	frontLeftMtr.move_absolute(d, 150);
	frontRightMtr.move_absolute(d, 142);
	backLeftMtr.move_absolute(d, 150);
	backRightMtr.move_absolute(d, 142);
}
void resetPositions(){
	backRightMtr.tare_position();
    backLeftMtr.tare_position();
    frontLeftMtr.tare_position();
    frontRightMtr.tare_position();
}
void leftTurn(int mult){ // 15 DEGREE INTERVALS
	resetPositions();
	int turn = mult * 138;//turn the 10 to be for about 15 degrees
	frontRightMtr.move_absolute(turn, 100);
	backRightMtr.move_absolute(turn, 100);
	frontLeftMtr.move_absolute(-turn, -100);
	backLeftMtr.move_absolute(-turn, -100);
}
void rightTurn(int mult){
	resetPositions();
	int turn = mult * 138;
	frontRightMtr.move_absolute(-turn, -100);
	backRightMtr.move_absolute(-turn, -100);
	backLeftMtr.move_absolute(turn, 100);
	frontLeftMtr.move_absolute(turn, 100);
	pros::lcd::print(1,"turn: %d", turn);
}
//MISC CONTROLS//
void motorStop() {
	for (int i = 0; i < 8; i++) {
		motors[i] = 0;
	}
}
void testfunct(){
	pros::lcd::print(0, "INIT auton1");
	//move forward to ball in front
	flywheel(true); // flywheel first, flameo - josh
	moveTo(3000);//this is pretty close - 2900 is perfect to intake the ball
	//pros::c::delay(1000);
	//turn on intake
	intake(1);

	pros::c::delay(3000);
	

	pros::c::delay(500);

	//turn right 135 degrees
	moveTo(-3200);
	pros::c::delay(1000);
	rightTurn(6);
	pros::c::delay(500);
	moveTo(-100);	

	//reaper and flywheel shoot
	//delay for flywheel to accelerate
	pros::c::delay(1000);
	reaper(1);
	pros::c::delay(2200);
	reaper(0);
	moveTo(2000);
	pros::c::delay(2000);
	reaper(1);
	pros::c::delay(3000);
	reaper(0);
}

void opcontrol() {

	//fuck this all jeez
	testfunct();

	// bool flyWheelToggle = false;
	// int intakeToggle = 0;
	// int reaperToggle = 0;
	// bool xPressed = false;
	// bool yPressed = false;
	// bool left = false;
	// bool right = false;
	// bool bPressed = false;
	// bool lPressed = false;
	// bool rPressed = false;

	// while (true) {

	// 	int driveLeft = master.get_analog(ANALOG_LEFT_Y);
	// 	int driveRight = master.get_analog(ANALOG_RIGHT_X);

	// 	if (master.get_digital(DIGITAL_X) == 1 && xPressed == false){
	// 		if (reaperToggle == 1){
	// 			reaperToggle = 0;
	// 		}
	// 		else if (reaperToggle == 0 || reaperToggle == -1){
	// 			reaperToggle = 1;
	// 		}
	// 		xPressed = true;


	// 	}
	// 	else if(master.get_digital(DIGITAL_X) == 0) {
	// 		xPressed = false;
	// 	}

	// 	if (master.get_digital(DIGITAL_B) == 1 && bPressed == false) {
	// 		if (reaperToggle == -1){
	// 			reaperToggle = 0;
	// 		}
	// 		else if (reaperToggle == 0 || reaperToggle == 1){
	// 			reaperToggle = -1;
	// 		}
	// 		bPressed = true;


	// 	}
	// 	else if (master.get_digital(DIGITAL_B) == 0) {
	// 		bPressed = false;
	// 	}

	// 	//intake toggling
	// 	if (master.get_digital(DIGITAL_LEFT) == 1 && lPressed == false ){

	// 		if (intakeToggle == 1){
	// 			intakeToggle = 0;
	// 		}
	// 		else if (intakeToggle == 0 || intakeToggle == -1){
	// 			intakeToggle = 1;
	// 		}
	// 		lPressed = true;

	// 	}
	// 	else if (master.get_digital(DIGITAL_LEFT) == 0){
	// 		lPressed = false;
	// 	}

	// 	if (master.get_digital(DIGITAL_RIGHT) == 1 && rPressed == false) {

	// 		if (intakeToggle == -1){
	// 			intakeToggle = 0;
	// 		}
	// 		else if (intakeToggle == 0 || intakeToggle == 1){
	// 			intakeToggle = -1;
	// 		}
	// 		rPressed = true;

	// 	}
	// 	else if (master.get_digital(DIGITAL_RIGHT) == 0){
	// 		rPressed = false;
	// 	}

	// 	//flywheel toggling
	// 	if (master.get_digital(DIGITAL_Y) == 1 && yPressed == false){
	// 		flyWheelToggle = !flyWheelToggle;
	// 		yPressed = true;
	// 		pros::Task::delay(20);
	// 	}
	// 	else if (master.get_digital(DIGITAL_Y) == 0){
	// 		yPressed = false;
	// 	}

	// 	// pros::lcd::print(2, "ARM: %d",(int)armMotor.get_position()) ;
	// 	if(master.get_digital(DIGITAL_R2) == 1){
	// 			armMotor = 100;
	// 	}
	// 	else if(master.get_digital(DIGITAL_L2) == 1){
	// 			armMotor = -100;
	// 	}
	// 	else if(armMotor.get_position() >= 400){
	// 		armMotor = -15;
	// 	}

	// 	else if(armMotor.get_position() < 400){
	// 		armMotor = 15;
	// 	}

	// 	if (master.get_digital(DIGITAL_UP) == 1) {
	// 		motorStop();
	// 	}
	// 	pros::lcd::print(1, "Reaper: %f Intake: %d", (reaperMotor.get_actual_velocity()),(int)intakeToggle);
	// 	pros::lcd::print(2, "Flywheel: %f", (flyWheelMotor.get_actual_velocity()));

	// 	intake(intakeToggle);
	// 	flywheel(flyWheelToggle);
	// 	drive(driveLeft, driveRight);
	// 	reaper(reaperToggle);
	// 	pros::Task::delay(20);

	// }
}