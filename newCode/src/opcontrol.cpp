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


//controler
pros::Controller master(pros::E_CONTROLLER_MASTER);

//drive motors
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);

//reaper
pros::Motor reaperMotor(5, pros::E_MOTOR_GEARSET_18, true);

//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7);

//arm (?)
pros::Motor armMotor(8);

// i honestly dont know why i have an array of motors - incase we need to iterate
pros::Motor motors [8] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, armMotor, reaperMotor};

void flywheel(bool toggle){
	if(toggle){
		flyWheelMotor = 127;
	}
	else {
		flyWheelMotor = 0;
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

void lift(){
	//we need to tune the motor so we know how long its supposed to be on
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

}
 
void motorStop() {
	for (int i = 0; i < 8; i++) {
		motors[i] = 0;
	}
}

void opcontrol() {
	pros::lcd::print(0, "INIT pumped up kicks is a fucking fire song (even if its about columbine)");
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
		pros::lcd::print(0, "hello this is initialized %d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	


		int driveLeft = master.get_analog(ANALOG_LEFT_Y); //controls left motors
		int driveRight = master.get_analog(ANALOG_RIGHT_Y);  //controls right motors

		//reaper toggling
		if (master.get_digital(DIGITAL_X) == 1 && xPressed == false){
			if (reaperToggle == 1)
			{
				reaperToggle = 0;
			}
			else if (reaperToggle == 0 || reaperToggle == -1)
			{
				reaperToggle = 1;
			}
			xPressed = true;
			
		 
		}
		else if(master.get_digital(DIGITAL_X) == 0) {
			xPressed = false;
		}
		if (master.get_digital(DIGITAL_B) == 1 && bPressed == false) {
			if (reaperToggle == -1)
			{
				reaperToggle = 0;
			}
			else if (reaperToggle == 0 || reaperToggle == 1)
			{
				reaperToggle = -1;
			}
			bPressed = true;


		}
		else if (master.get_digital(DIGITAL_B) == 0) {
			bPressed = false;
		}
		

		//intake toggling
		if (master.get_digital(DIGITAL_LEFT) == 1 && lPressed == false ){
			
			if (intakeToggle == 1)
			{
				intakeToggle = 0;
			}
			else if (intakeToggle == 0 || intakeToggle == -1)
			{
				intakeToggle = 1;
			}
			lPressed = true;
		
		}
		else if (master.get_digital(DIGITAL_LEFT) == 0)
		{
			lPressed = false;
		}
		if (master.get_digital(DIGITAL_RIGHT) == 1 && rPressed == false) {

			if (intakeToggle == -1)
			{
				intakeToggle = 0;
			}
			else if (intakeToggle == 0 || intakeToggle == 1)
			{
				intakeToggle = -1;
			}
			rPressed = true;

		}
		else if (master.get_digital(DIGITAL_RIGHT) == 0)
		{
			rPressed = false;
		}

		
		
		

		//flywheel toggling
		if (master.get_digital(DIGITAL_Y) == 1 && yPressed == false){
			flyWheelToggle = !flyWheelToggle;
			yPressed = true;
			pros::Task::delay(20);
		}
		else if (master.get_digital(DIGITAL_Y) == 0)
		{
			yPressed = false;
		}
	
		//stops all motors
		if (master.get_digital(DIGITAL_UP) == 1) {
			motorStop();
		}
		pros::lcd::print(3, "Reaper Motor Speed: %f", (reaperMotor.get_actual_velocity()));
		pros::lcd::print(2, "Intake Motor Speed: %d",(int)intakeToggle) ;
		pros::lcd::print(1, "Flywheel Speed: %f", (flyWheelMotor.get_actual_velocity()));
	
		intake(intakeToggle);
		flywheel(flyWheelToggle);
		drive(driveLeft, driveRight);
		reaper(reaperToggle);
		pros::Task::delay(20);

	}
}

//rc and lc are left and right coeffs 
void moveTo(double d, int RC, int LC){
	double kpl = 1;
	double kpr = 1;
	if(RC + LC == 0){
		//turning
		kpr = 1;
		kpl = 1;
	}
	while(abs(d - frontLeftMtr.get_position()) > 5){
		frontRightMtr.move((abs(d - frontRightMtr.get_position()) * kpr) * RC);
		frontLeftMtr.move((abs(d - frontLeftMtr.get_position()) * kpl)*LC);
		backLeftMtr.move((abs(d - backLeftMtr.get_position()) * kpl)*LC);
		backRightMtr.move((abs(d - backRightMtr.get_position()) * kpr)*RC);
		pros::lcd::print(0, "overshoot: %f", d - frontLeftMtr.get_position());
	}  

}

