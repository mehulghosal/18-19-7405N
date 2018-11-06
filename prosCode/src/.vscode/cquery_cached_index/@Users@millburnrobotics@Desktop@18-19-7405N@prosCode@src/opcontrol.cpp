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
pros::Motor backLeftMtr(1);
pros::Motor backRightMtr(2);
pros::Motor frontLeftMtr(3);
pros::Motor frontRightMrt(4);



//until we get more motor wires, we wont be able to declare all of the motors - upload error
//flywheel
pros::Motor flyWheelMotor(6);

//intake
pros::Motor intakeMotor(7);

//lift (?)
pros::Motor liftMotor(8);

pros::Motor motors [7] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMrt, flyWheelMotor, intakeMotor, liftMotor};
// i honestly dont know why i have an array of motors - incase we need to iterate


void flywheel(){
	flyWheelMotor = 127;
	pros::lcd::print(0, "Flywheel Speed: %d", (flyWheelMotor.get_actual_velocity()));
}

void intake(){
	intakeMotor = -127;
	pros::lcd::print(1, "Intake Motor SPEEd: %d", (intakeMotor.get_actual_velocity()));
}


void opcontrol() {
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int driveX = master.get_analog(ANALOG_RIGHT_X); //controls right and left
		int driveY = master.get_analog(ANALOG_LEFT_Y);  //controls forward/back

		int flyOn = master.get_digital(DIGITAL_Y);		//only flywheel
		int intakeOn = master.get_digital(DIGITAL_A);	//only intake
		int powerOff = master.get_digital(DIGITAL_B);	//turn of all motors

		if (flyOn == 1){
			flywheel();
		}
		if(intakeOn == 1){
			intake();
		}



		//backRightMtr, frontRightMrt = right;
		//backLeftMtr, frontLeftMtr = left;
		//backLeftMtr = left;
		//backRightMtr = right;

	}
}

void drive(){


}

void lift(){


}