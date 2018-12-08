#include "main.h"
#include "fps.cpp"

void resetPositions();
//CONTROLLER
pros::Controller master(pros::E_CONTROLLER_MASTER);

//MOTOR INITS//
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(4, pros::E_MOTOR_GEARSET_18, true);
pros::Motor reaperMotor(5, pros::E_MOTOR_GEARSET_18, true);
pros::Motor flyWheelMotor(6);
pros::Motor intakeMotor(7);
pros::Motor armMotor(8);
pros::Motor motors [8] = {backLeftMtr, backRightMtr, frontLeftMtr, frontRightMtr, flyWheelMotor, intakeMotor, armMotor, reaperMotor};

//OPCONTROL DRIVE//

// VISION SENSOR STUFF//
//https://www.vexforum.com/index.php/attachment/5be56e847b3f6_1.png

pros::vision_signature_s_t red_flag = {1,{255,255,255},8755,9319,9036,1269,1943,1606,3,0};
/*
typedef struct __attribute__((__packed__)) vision_signature {
  uint8_t id;
  uint8_t _pad[3];
  float range;
  int32_t u_min;
  int32_t u_max;
  int32_t u_mean;
  int32_t v_min;
  int32_t v_max;
  int32_t v_mean;
  uint32_t rgb;
  uint32_t type;
} vision_signature_s_t;
*/

/*
id	The signature id.
uMin	The signature minimum value on the u axis.
uMax	The signature maximum value on the u axis.
uMean	The signature mean value on the u axis.
vMin	The signature minimum value on the v axis.
vMax	The signature maximum value on the v axis.
vMean	The signature mean value on the v axis.
range	The signature range scale factor.
type	The signature type, normal or color code.
*/

void chassisSet(int m1, int m2){
	backLeftMtr = m1;
	frontLeftMtr = m1;
	backRightMtr = m2;
	frontRightMtr = m2;
}

// void updatePosition(int posChange, int gyroAngle);


void leftTurn(double mult, int speed = 100){ //  DEGREE INTERVALS
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

void rightTurn(double mult, int speed = 100){
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
		armMotor = 0;
	}
	else{
		armMotor.move_absolute(-100, 100);
		armMotor = -0;
	}
}

//AUTON CONTROLS//

void moveTo(double d){
	resetPositions();
	int speed = 0;
	double slowdown = (4 * d) / 5;
	if(d > 0)
	{
while(frontLeftMtr.get_position() < d && frontRightMtr.get_position() < d)
{
	double le = frontLeftMtr.get_position();
	double re = frontRightMtr.get_position();
	double ble = backLeftMtr.get_position();
	double diff = le - re;
	double samesidediff = le - ble;
	double adjust = 90 + (2 * diff);
	double samesideadjust = 90 + (2 * samesidediff);
	frontLeftMtr = 90;
	frontRightMtr= adjust;
	backLeftMtr = samesideadjust;
	backRightMtr= adjust;
	pros::lcd::print(1, "Entered firstLoop");
	pros::lcd::print(2, "fLeft encoder: %f", le);
	pros::lcd::print(3, "fright encoder: %f", re);
	pros::lcd::print(4, "bleft encoder: %f", backLeftMtr.get_position());
	pros::lcd::print(5, "bright encoder: %f", backRightMtr.get_position());
		pros::lcd::print(6, "slowdown %f", slowdown);
			pros::c::delay(50);

}
}
if ( d < 0)
{
	while(frontLeftMtr.get_position() > d && frontRightMtr.get_position() > d)
	{
		double le = frontLeftMtr.get_position();
		double re = frontRightMtr.get_position();
		double ble = backLeftMtr.get_position();
		double diff = le - re;
		double samesidediff = le - ble;
		double adjust = -90 + (2 * diff);
		double samesideadjust = -90 + (2 * samesidediff);
		frontLeftMtr = -90;
		frontRightMtr= adjust;
		backLeftMtr = samesideadjust;
		backRightMtr= adjust;
		pros::lcd::print(1, "Entered firstLoop");
		pros::lcd::print(2, "fLeft encoder: %f", le);
		pros::lcd::print(3, "fright encoder: %f", re);
		pros::lcd::print(4, "bleft encoder: %f", backLeftMtr.get_position());
		pros::lcd::print(5, "bright encoder: %f", backRightMtr.get_position());
			pros::lcd::print(6, "slowdown %f", slowdown);
				pros::c::delay(50);

	}
}/*while(frontLeftMtr.get_position() < d && frontRightMtr.get_position() < d)
{
	double le = frontLeftMtr.get_position();
	double re = frontRightMtr.get_position();
	double diff = le - re;
	double adjust = 30 + (2 * diff);
	chassisSet(30, adjust );
	pros::lcd::print(1, "Entered second Loop");
	pros::lcd::print(2, "Left encoder: %f", le);
	pros::lcd::print(3, "right encoder: %f", re);
	pros::lcd::print(4, "bleft encoder: %f", backLeftMtr.get_position());
	pros::lcd::print(5, "bright encoder: %f", backRightMtr.get_position());
		pros::lcd::print(6, "slowdown %f", slowdown);
		pros::c::delay(50);
*/

	chassisSet(0, 0 );
	pros::c::delay(1000);
	}

void moveTo(double d, int speedCoef){
	resetPositions();
	int speed = 0;
	double slowdown = (4 * d) / 5;
	if(d > 0)
	{
while(frontLeftMtr.get_position() < d && frontRightMtr.get_position() < d)
{
	double le = frontLeftMtr.get_position();
	double re = frontRightMtr.get_position();
	double ble = backLeftMtr.get_position();
	double diff = le - re;
	double samesidediff = le - ble;
	double adjust =  speedCoef + (2 * diff);
	double samesideadjust = speedCoef + (2 * samesidediff);
	frontLeftMtr = speedCoef;
	frontRightMtr= adjust;
	backLeftMtr = samesideadjust;
	backRightMtr= adjust;
	pros::lcd::print(1, "Entered firstLoop");
	pros::lcd::print(2, "fLeft encoder: %f", le);
	pros::lcd::print(3, "fright encoder: %f", re);
	pros::lcd::print(4, "bleft encoder: %f", backLeftMtr.get_position());
	pros::lcd::print(5, "bright encoder: %f", backRightMtr.get_position());
		pros::lcd::print(6, "slowdown %f", slowdown);
			pros::c::delay(50);

}
}
if ( d < 0)
{
	while(frontLeftMtr.get_position() > d && frontRightMtr.get_position() > d)
	{
		double le = frontLeftMtr.get_position();
		double re = frontRightMtr.get_position();
		double ble = backLeftMtr.get_position();
		double diff = le - re;
		double samesidediff = le - ble;
		double adjust = -speedCoef + (2 * diff);
		double samesideadjust = -speedCoef + (2 * samesidediff);
		frontLeftMtr = -speedCoef;
		frontRightMtr= adjust;
		backLeftMtr = samesideadjust;
		backRightMtr= adjust;
		pros::lcd::print(1, "Entered firstLoop");
		pros::lcd::print(2, "fLeft encoder: %f", le);
		pros::lcd::print(3, "fright encoder: %f", re);
		pros::lcd::print(4, "bleft encoder: %f", backLeftMtr.get_position());
		pros::lcd::print(5, "bright encoder: %f", backRightMtr.get_position());
			pros::lcd::print(6, "slowdown %f", slowdown);
				pros::c::delay(50);

	}

}
chassisSet(0,0);
}

//pid - work with this l8r
//todo: do the thing josh was talkign about with tracking velocties
//if velo < some value: turn off all motors, but also make sure time is greater than 100
//also incorporate chasiset for turning



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
//	testfunct();
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
	pros::ADIDigitalIn limit ('A');
//	pros::ADIAnalogIn gyroscope ('B');

//	gyroscope.calibrate();
	while (true) {

		int driveLeft = master.get_analog(ANALOG_LEFT_Y);
		int driveRight = master.get_analog(ANALOG_RIGHT_X);





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
		if(master.get_digital(DIGITAL_R1) == 1){
				armMotor = 100;
		}
		else if(master.get_digital(DIGITAL_L1) == 1){
				armMotor = -100;
		}
		else if(armMotor.get_position() >= 400){
			armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			armMotor = 0;
		}

		else if(armMotor.get_position() < 400){
			armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			armMotor = 0;
		}

		if (master.get_digital(DIGITAL_UP) == 1) {
			motorStop();
		}
		intake(intakeToggle);
		flywheel(flyWheelToggle);
		drive(driveLeft, driveRight);
		reaper(reaperToggle);
		prevTravelDist = frontLeftMtr.get_position();

		pros::lcd::print(1, "Reaper: %f Intake: %d", (reaperMotor.get_actual_velocity()),(int)intakeToggle);
		pros::lcd::print(2, "Flywheel: %f", (flyWheelMotor.get_actual_velocity()));
	//	pros::lcd::print(3, "GYRO: %d", (gyroscope.get_value()));

		pros::Task::delay(20);

	}
}
