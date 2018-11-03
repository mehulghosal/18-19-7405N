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
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);


//reaper
pros::Motor reaperMotor(5);

//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7, pros::E_MOTOR_GEARSET_18, true);

//arm (?)
pros::Motor armMotor(8);

pros::Motor motors [8] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, armMotor, reaperMotor};
// i honestly dont know why i have an array of motors - incase we need to iterate


int flySpeedToggle = 0;
void flywheel(bool toggle){
	if(toggle){
		flyWheelMotor = 127;
	}
	else {
		flyWheelMotor = 0;
	}
	
	pros::lcd::print(1, "Flywheel Speed: %f", (flyWheelMotor.get_actual_velocity()));
	pros::c::delay(100);
}

void intake(bool toggle){
	if(toggle == 1){
		intakeMotor = 127;
	}
	else{
		intakeMotor = -127;
	}
	pros::lcd::print(2, "Intake Motor Speed: %f", (intakeMotor.get_actual_velocity()));
}

void reaper(bool toggle){
	if(toggle == 1){
		reaperMotor = 127;
	}
	else if(toggle == 0){
		reaperMotor = 0;
	}

	pros::lcd::print(3, "Reaper Motor Speed: %f", (reaperMotor.get_actual_velocity()));
}

void motorStop() {
	for (int i = 0; i < 8; i++) {
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

	pros::lcd::print(4, "BL : %d", (backLeftMtr.get_actual_velocity()));
	pros::lcd::print(5, "FL : %d", (frontLeftMtr.get_actual_velocity()));
	pros::lcd::print(6, "BR : %d", (backRightMtr.get_actual_velocity()));
	pros::lcd::print(7, "FR : %d", (frontRightMtr.get_actual_velocity()));

	//pros::lcd::print(5, "Drive motor speeds : %d", (bLS));
	//pros::lcd::print(6, "Drive motor speeds : %d", (bLS));

					 /*backLeftMtr.get_actual_velocity(),
					 frontRightMtr.get_actual_velocity(),
					 frontLeftMtr.get_actual_velocity()));*/
}

void lift(){
	//we need to tune the motor so we know how long its supposed to be on
}

void opcontrol() {
	pros::lcd::print(0, "INIT pumped up kicks is a fucking fire song (even if its about columbine)");
	bool flyWheelToggle = 0;
	bool intakeToggle = 0;
	bool reaperToggle = 0;

	while (true) {
		pros::lcd::print(0, "hello this is initialized %d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);


		int driveLeft = master.get_analog(ANALOG_LEFT_Y); //controls left motors
		int driveRight = master.get_analog(ANALOG_RIGHT_Y);  //controls right motors


		if (master.get_digital(DIGITAL_Y) == 1)
		{
			reaperToggle = !reaperToggle;
		}
		//intake toggling
		if(master.get_digital(DIGITAL_A) == 1){
			intakeToggle = !intakeToggle;
		
		
		}

		//flywheel toggling
		if(master.get_digital(DIGITAL_X) == 1){
			flyWheelToggle = !flyWheelToggle;
			
		}
		


		if (master.get_digital(DIGITAL_L1) == 1) {
			motorStop();
		}

		intake(intakeToggle);
		flywheel(flyWheelToggle);
		drive(driveLeft, driveRight);
		reaper(reaperToggle);
		pros::Task::delay(50);
		

		//backRightMtr, frontRightMrt = right;
		//backLeftMtr, frontLeftMtr = left;
		//backLeftMtr = left;
		//backRightMtr = right;


	}
}

void auton1(){
	pros::lcd::print(0, "INIT auton1");
}

void leftTurn(){
	//90 degree left turn: right side 100, left side -100
	//we have to do PID so we know how long the motors should stay on
}

void rightTurn(){
	//same as the other method ig
}
