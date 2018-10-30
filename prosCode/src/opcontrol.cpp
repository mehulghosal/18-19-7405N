#include "main.h"


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


//declaring global vars, controler
pros::Controller master(pros::E_CONTROLLER_MASTER);

//drive motors
pros::Motor backLeftMtr(9);
pros::Motor backRightMtr(1);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2);

//until we get more motor wires, we wont be able to declare all of the motors - upload error
//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7);

//lift (?)
pros::Motor liftMotor(8);

pros::Motor motors [7] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, liftMotor};
// i honestly dont know why i have an array of motors - incase we need to iterate

void flywheel(int toggle){
	if(toggle == 1){
		flyWheelMotor = 127;
	}
	else{
		flyWheelMotor = 0;
	}
	pros::lcd::print(0, "Flywheel Speed: %d", (flyWheelMotor.get_actual_velocity()));
}

void intake(int toggle){
	if(toggle == 1){
		intakeMotor = -127;
	}
	else{
		intakeMotor = 0;
	}
	pros::lcd::print(1, "Intake Motor Speed: %d", (intakeMotor.get_actual_velocity()));
}

void motorStop() {
	for (int i = 0; i < 7; i++) {
		motors[i] = 0;
	}
}

void drive(int driveL, int driveR) {

	if(driveL > 15 || driveL < -15){
		backLeftMtr = driveL; frontLeftMtr = driveL;
	}
	else{
		backLeftMtr = 0; frontLeftMtr = 0;
	}
	if(driveR > 15 || driveR < -15){
		backRightMtr = driveR; frontRightMtr = driveR;
	}
	else{
		backRightMtr = 0; frontRightMtr = 0;
	}

	pros::lcd::print(1, "Drive motor speeds (BR, BL, FR, FL): %d %d %d %d", (backRightMtr.get_actual_velocity(),
					 backLeftMtr.get_actual_velocity(),
					 frontRightMtr.get_actual_velocity(),
					 frontLeftMtr.get_actual_velocity()));
}

void lift(){


}

void opcontrol() {
	pros::lcd::print(0, "INIT pumped up kicks is a fucking fire song (even if its about columbine)");
	int flyWheelToggle = 0;
	int intakeToggle = 0;

	while (true) {
		pros::lcd::print(0, "hello this is initialized %d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		int driveLeft = master.get_analog(ANALOG_LEFT_Y); //controls left motors
		int driveRight = master.get_analog(ANALOG_RIGHT_Y);  //controls right motors

		//intake toggling
		if(master.get_digital(DIGITAL_Y) == 1){
			intakeToggle = 1;
		}
		else if(master.get_digital(DIGITAL_A) == 1){
			intakeToggle = 0;
		}

		//flywheel toggling
		if(master.get_digital(DIGITAL_X) == 1){
			flyWheelToggle = 1;
		}
		else if(master.get_digital(DIGITAL_B) == 1){
			flyWheelToggle = 0;
		}

		
		if (master.get_digital(DIGITAL_L1) == 1) {
			motorStop();
		}

		intake(intakeToggle);
		flywheel(flyWheelToggle);
		drive(driveLeft, -driveRight);

		//backRightMtr, frontRightMrt = right;
		//backLeftMtr, frontLeftMtr = left;
		//backLeftMtr = left;
		//backRightMtr = right;

	}
}

void auton1(){
	pros::lcd::print(0, "INIT auton1");
}