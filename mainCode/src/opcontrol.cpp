#include "main.h"

void resetPositions();
//CONTROLLER
pros::Controller master(pros::E_CONTROLLER_MASTER);

//MOTOR INITS//
pros::Motor backLeftMtr(9);
pros::Motor frontLeftMtr(10);
pros::Motor frontRightMtr(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor backRightMtr(1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor reaperMotor(6, pros::E_MOTOR_GEARSET_06, true);
pros::Motor flyWheelMotor(4, pros::E_MOTOR_GEARSET_18);
pros::Motor intakeMotor(3);
pros::Motor armMotor(8);

pros::Motor motors[8] = {
	backLeftMtr,
	backRightMtr,
	frontLeftMtr,
	frontRightMtr,
	flyWheelMotor,
	intakeMotor,
	armMotor,
	reaperMotor
};
pros::ADIAnalogIn linesens('E');
pros::ADIAnalogIn linesens2('B');
void changeFlywheel(bool change);
double getflywheelspeed()
{
	return flyWheelMotor.get_actual_velocity();
}
void setFlywheelspeed(int speed)
{
	flyWheelMotor = speed;
}
void setBrake()
{

	backLeftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	backRightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	frontLeftMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	frontRightMtr.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}
void old_flywheel(bool toggle, int speed = 127)
{
	if (toggle)
	{
		flyWheelMotor = speed;
	}
	else
	{
		flyWheelMotor = 0;
	}
}



void changeArm(int val)
{
	armMotor = val;
	armMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}
// VISION SENSOR STUFF//
//https://www.vexforum.com/index.php/attachment/5be56e847b3f6_1.png
void display()
{
	pros::lcd::print(3, "fLeft: %f | fright: %f", frontLeftMtr.get_position(), frontRightMtr.get_position());
	pros::lcd::print(4, "bleft: %f | bright: %f", backLeftMtr.get_position(), backRightMtr.get_position());
	pros::lcd::print(5, "flywheel %f", getflywheelspeed());
}

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

//DRIVE FUNCTION//
/*PARAMS:
 *m1 = left side motor speed
 *m2 = right side motor speed
 */
void chassisSet(int m1, int m2)
{
	backLeftMtr = m1;
	frontLeftMtr = m1;
	backRightMtr = m2;
	frontRightMtr = m2;
}

pros::vision_signature_s_t convert_sig(	int32_t id,
	int32_t uMin,
	int32_t uMax,
	int32_t uMean,
	int32_t vMin,
	int32_t vMax,
	int32_t vMean,
	float range,
	int32_t type)
{
	pros::vision_signature_s_t sig;
	sig.id = id;
	sig.u_min = uMin;
	sig.u_max = uMax;
	sig.u_mean = uMean;
	sig.v_min = vMin;
	sig.v_max = vMax;
	sig.v_mean = vMean;
	sig.range = range;
	sig.type = type;
	return sig;
}

void PrintReadableVisObj(pros::vision_object_s_t inp)
{
	printf("SIG: %lf | LEFT_COORD: %lf | TOP_COORD: %lf | WIDTH: %lf | HEIGHT: %lf \n X_MID: %lf | Y_MID: %lf",
		inp.signature,
		inp.left_coord,
		inp.top_coord,
		inp.width,
		inp.height,
		inp.x_middle_coord,
		inp.y_middle_coord
);
}

pros::Vision vision_sensor(7);

pros::vision_signature_s_t RED_FLAG = convert_sig(1, 6425, 9505, 7965, -203, 819, 308, 3, 0);

//AUTON MOVE CONTROLS//
void leftTurn(double mult, int speed = 100)
{ //  DEGREE INTERVALS
	resetPositions();
	int turn = (int)(mult * 8.52);
	frontRightMtr.move_absolute(turn, speed);
	backRightMtr.move_absolute(turn, speed);
	frontLeftMtr.move_absolute(-turn, -speed);
	backLeftMtr.move_absolute(-turn, -speed);
	pros::lcd::print(1, "turn: %d", turn);

	while (std::abs(frontRightMtr.get_position() - turn) > 15)
	{
		pros::c::delay(20);
	}
}

void rightTurn(double mult, int speed = 100)
{
	resetPositions();
	int turn = (int)(mult * 8.54); // 128 before
	frontRightMtr.move_absolute(-turn, -speed);
	backRightMtr.move_absolute(-turn, -speed);
	backLeftMtr.move_absolute(turn, speed);
	frontLeftMtr.move_absolute(turn, speed);
	pros::lcd::print(1, "turn: %d", turn);

	while (std::abs(backLeftMtr.get_position() - turn) > 15)
	{
		pros::c::delay(20);
	}
}

int controllerDampen(int controllerOutput, double power)
{
	double answer = 127.0 *std::pow(controllerOutput / 127.0, power);
	int roundedAnswer = (int) std::round(answer);
	return roundedAnswer;
}

void drive(int driveL, int driveR)
{
	int d = controllerDampen(driveL, 9 / 7);
	int t = controllerDampen(driveR, 9 / 7);
	chassisSet(d + t, d - t);
	setBrake();
	resetPositions();
}

//OTHER FEATURE CONTROLS//

void flywheel(bool toggle, int speed = 200)
{
	if (toggle)
	{

		flyWheelMotor.move_velocity(speed);
	}
	else
	{
		flyWheelMotor = 0;
	}
	//	pros::lcd::print(3, "flywheel %d", flyWheelMotor.get_actual_velocity());
}
void reaper(int toggle, int speed = 127)
{
	if (toggle == 1)
	{
		reaperMotor = speed;
	}
	else if (toggle == 0)
	{
		reaperMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
		reaperMotor = 0;

	}
	else
	{
		reaperMotor = -speed;
	}
}

void moveReaper(int dist, bool delay)
{
	reaperMotor.move_relative(dist, 150);

	if (delay)
	{
		while (std::abs(reaperMotor.get_position() - dist) > 15)
		{
			pros::c::delay(10);
		}
	}
}
void intake(int toggle)
{
	if (toggle == 1)
	{
		intakeMotor = 127;
	}
	if (toggle == -1)
	{
		intakeMotor = -127;
	}
	if (toggle == 0)
	{
		intakeMotor = 0;
	}
}
void arm(bool toggle)
{
	if (toggle == true)
	{
		armMotor.move_absolute(100, 100);
		armMotor = 0;
	}
	else
	{
		armMotor.move_absolute(-100, 100);
		armMotor = -0;
	}
}

void moveTo(double d)
{
	resetPositions();

	double speedCoef = 0;
	double slowdown = (4 *d) / 5;
	double sdiff = 0;
	double ssamesidediff = 0;
	double sbackrightadjust = 0;
	double mdiff = 0;
	double msamesidediff = 0;
	double mbackrightadjust = 0;

	if (d > 0)
	{
		while (frontLeftMtr.get_position() < d && frontRightMtr.get_position() < d)
		{
			double kp = .10;

			if (abs(d - frontLeftMtr.get_position()) *kp > 127)
			{
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();

				double diff = .1 *(le - re);
				double samesidediff = .1 *(le - ble);
				double backrightadjust = .1 *(le - bre);
				speedCoef = 100;
				frontLeftMtr = speedCoef;
				frontRightMtr = speedCoef + diff;
				backLeftMtr = speedCoef + samesidediff;
				backRightMtr = speedCoef + backrightadjust;
				// while the robot is traveling at optimal speeds it finds the difference between encoders
				// it then uses this value to adjust by adding and subtracting a fractional part of it to the motors

			}
			else if (abs(d - frontLeftMtr.get_position()) *kp < 10)
			{
				speedCoef = 10;
				frontLeftMtr = speedCoef;
				frontRightMtr = speedCoef + sdiff;
				backLeftMtr = speedCoef + ssamesidediff;
				backRightMtr = speedCoef + sbackrightadjust;
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();
				sdiff = .1 *(le - re);
				ssamesidediff = .1 *(le - ble);
				sbackrightadjust = .1 *(le - bre);
				// when the bot is close to its final destination is travels at 10 speed until it reaches
				// I use different variables because I want to restart the values at 0.
				// this is why i set sdiff after i assign the speeds

			}
			else
			{
				speedCoef = abs(d - frontLeftMtr.get_position()) *kp;
				frontLeftMtr = speedCoef;
				frontRightMtr = speedCoef + mdiff;
				backLeftMtr = speedCoef + msamesidediff;
				backRightMtr = speedCoef + mbackrightadjust;
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();
				mdiff = .1 *(le - re);
				msamesidediff = .1 *(le - ble);
				mbackrightadjust = .1 *(le - bre);
				// while bot approaches the final destination, the speed slows down
			}

			pros::c::delay(170);
		}

		chassisSet(0, 0);
	}

	if (d < 0)
	{
		while (frontLeftMtr.get_position() > d && frontRightMtr.get_position() > d)
		{
			double kp = .1;

			if (abs(d - frontLeftMtr.get_position()) *kp > 127)
			{
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();

				double diff = .1 *(le - re);
				double samesidediff = .1 *(le - ble);
				double backrightadjust = .1 *(le - bre);
				speedCoef = 100;
				frontLeftMtr = -speedCoef;
				frontRightMtr = -speedCoef + diff;
				backLeftMtr = -speedCoef + samesidediff;
				backRightMtr = -speedCoef + backrightadjust;

			}
			else if (abs(d - frontLeftMtr.get_position()) *kp < 20)
			{
				speedCoef = 25;
				frontLeftMtr = -speedCoef;
				frontRightMtr = -speedCoef + sdiff;
				backLeftMtr = -speedCoef + ssamesidediff;
				backRightMtr = -speedCoef + sbackrightadjust;
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();
				sdiff = .1 *(le - re);
				ssamesidediff = .1 *(le - ble);
				sbackrightadjust = .1 *(le - bre);
			}
			else
			{
				speedCoef = abs(d - frontLeftMtr.get_position()) *kp;
				frontLeftMtr = -speedCoef;
				frontRightMtr = -speedCoef + mdiff;
				backLeftMtr = -speedCoef + msamesidediff;
				backRightMtr = -speedCoef + mbackrightadjust;
				double le = frontLeftMtr.get_position();
				double re = frontRightMtr.get_position();
				double ble = backLeftMtr.get_position();
				double bre = backRightMtr.get_position();
				mdiff = .1 *(le - re);
				msamesidediff = .1 *(le - ble);
				mbackrightadjust = .1 *(le - bre);
			}

			pros::c::delay(150);

		}

		chassisSet(0, 0);
	}
	setBrake();
	chassisSet(0, 0);
	pros::c::delay(300);
}
void moveTo(double d, double speed)
{
	resetPositions();

	double speedCoef = 0;
	double slowdown = (4 *d) / 5;

	if (d > 0)
	{
		while (frontLeftMtr.get_position() < d && frontRightMtr.get_position() < d)
		{
			double le = frontLeftMtr.get_position();
			double re = frontRightMtr.get_position();
			double ble = backLeftMtr.get_position();
			double bre = backRightMtr.get_position();
			double diff = le - re;
			double kp = .1;
			diff = .1 *diff;
			double samesidediff = le - ble;
			samesidediff = samesidediff *.1;
			double backrightadjust = .1 *(le - bre);
			double adjust = speedCoef + (2 *diff);
			double samesideadjust = speedCoef + (2 *samesidediff);
			if (abs(d - frontRightMtr.get_position()) *kp > 127)
			{
				speedCoef = 80;
			}
			else if (abs(d - frontRightMtr.get_position()) *kp < 10)
			{
				speedCoef = 10;
			}
			else
			{
				speedCoef = abs(d - frontRightMtr.get_position()) *kp;
			}

			frontLeftMtr = speed;
			frontRightMtr = speed + diff;
			backLeftMtr = speed + samesidediff;
			backRightMtr = speed + backrightadjust;

			//	pros::lcd::print(1, "Entered firstLoop");
			//	pros::lcd::print(3, "fLeft encoder: %f | fright encoder: %f", le, re);
			//	pros::lcd::print(4, "bleft encoder: %f | bright encoder: %f", backLeftMtr.get_position(), backRightMtr.get_position());
			//	pros::lcd::print(6, "diff %f", diff);
			pros::c::delay(170);
		}
		setBrake();
		chassisSet(0, 0);
	}

	if (d < 0)
	{
		while (frontLeftMtr.get_position() > d && frontRightMtr.get_position() > d)
		{
			double le = frontLeftMtr.get_position();
			double re = frontRightMtr.get_position();
			double ble = backLeftMtr.get_position();
			double bre = backRightMtr.get_position();
			double diff = le - re;
			double kp = .1;
			diff = .1 *diff;
			double samesidediff = le - ble;
			samesidediff = samesidediff *.1;
			double backrightadjust = .1 *(le - bre);
			if (abs(d - frontRightMtr.get_position()) *kp > 127)
			{
				speedCoef = 80;
			}
			else if (abs(d - frontRightMtr.get_position()) *kp < 20)
			{
				speedCoef = 20;
			}
			else
			{
				speedCoef = abs(d - frontRightMtr.get_position()) *kp;
			}

			frontLeftMtr = -speed;
			frontRightMtr = -speed + diff;
			backLeftMtr = -speed + samesidediff;
			backRightMtr = -speed + backrightadjust;

			//	pros::lcd::print(1, "Entered firstLoop");
			///	pros::lcd::print(3, "fLeft encoder: %f | fright encoder: %f", le, re);
			//	pros::lcd::print(4, "bleft encoder: %f | bright encoder: %f", backLeftMtr.get_position(), backRightMtr.get_position());
			//	pros::lcd::print(6, "diff %f", diff);
			pros::c::delay(50);

		}
		setBrake();
		chassisSet(0, 0);
	}
	setBrake();
	chassisSet(0, 0);
	pros::c::delay(300);
	//	pros::lcd::print(1, "Entered firstLoop");
	//	pros::lcd::print(3, "fLeft: %f | fright: %f", frontLeftMtr.get_position(), frontRightMtr.get_position());
	//	pros::lcd::print(4, "bleft: %f | bright: %f", backLeftMtr.get_position(), backRightMtr.get_position());

}

int getLimit()
{
	if (linesens.get_value() <= 1500 || linesens2.get_value() <= 1500)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void resetPositions()
{
	backRightMtr.tare_position();
	backLeftMtr.tare_position();
	frontLeftMtr.tare_position();
	frontRightMtr.tare_position();
}

void motorStop()
{
	for (int i = 0; i < 8; i++)
	{
		motors[i] = 0;
	}
}

//FOR TESTING CODE//
void testfunct()
{

}

void opcontrol()
{

	//fuck this all jeez
	//	testfunct();
	changeFlywheel(false);
	flywheel(true, 195);
	int disp = 0;
	int prevTravelDist = 0;
	int flyWheelSpeed = 200;
	bool flyWheelToggle = false;
	int intakeToggle = 0;
	int reaperToggle = 0;
	bool r2Pressed = false;
	bool r1Pressed = false;
	bool left = false;
	bool right = false;
	bool bPressed = false;
	bool l2Pressed = false;
	bool lPressed = false;
	bool autoReap = false;
	bool rPressed = false;
	bool xPressed = false;
	bool rumbCon = false;
	int currentarm = 0;
	//pros::ADIDigitalIn limit ('A');
	//	pros::ADIAnalogIn gyroscope ('B');
	//	pros::Vision::print_signature(RED_FLAG);
	//	gyroscope.calibrate();

	pros::vision_object_s_t *read_arr = new pros::vision_object_s_t[5];

	while (true)
	{

		int driveLeft = master.get_analog(ANALOG_LEFT_Y);
		int driveRight = master.get_analog(ANALOG_RIGHT_X);

		vision_sensor.read_by_size(1, 5, read_arr);
		PrintReadableVisObj(read_arr[0]);

		if (master.get_digital(DIGITAL_R2) == 1 && r2Pressed == false)
		{
			if (getLimit() == 1 && reaperToggle == 1)
			{
				reaperToggle = 0;

			}
			else if (getLimit() == 1 && reaperToggle == 0)
			{
				master.print(0, 0, "        ");
				reaperToggle = 1;
				reaper(reaperToggle);
				pros::c::delay(350);
			}
			else if (reaperToggle == 0 || reaperToggle == -1)
			{
				master.print(0, 0, "          ");
				reaperToggle = 1;
			}
			else if (reaperToggle == 1)
			{
				master.print(0, 0, "          ");
				reaperToggle = 0;
			}
			r2Pressed = true;
		}
		else if (master.get_digital(DIGITAL_R2) == 0)
		{

			if (getLimit() == 1 && reaperToggle == 1)
			{
				master.print(0, 0, "Ball");

				reaperToggle = 0;
			}
			else if (getLimit() == 1 && reaperToggle == 0)
			{
				master.print(0, 0, "Ball");
				reaperToggle = 0;
			}
			if (getLimit() == 0)
			{
				master.print(0, 0, "          ");
			}
			r2Pressed = false;
		}
		if (master.get_digital(DIGITAL_X) == 1)
		{
			master.print(2, 0, "Doubleshot");
			reaper(1, 115);
			moveTo(2500, 127);
			master.print(2, 0, "            ");
		}

		if (master.get_digital(DIGITAL_B) == 1 && bPressed == false)
		{
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
		else if (master.get_digital(DIGITAL_B) == 0)
		{
			bPressed = false;
		}

		//intake toggling


		intakeToggle = 0;
		if (master.get_digital(DIGITAL_L2) == 1)
		{
			/*
			      if (intakeToggle == 1) {
			        intakeToggle = 0;
			      } else if (intakeToggle == 0 || intakeToggle == -1) {
			        intakeToggle = 1;
			      } */
			intakeToggle = 1;

		}
		else if (master.get_digital(DIGITAL_L2) == 0)
		{
			lPressed = false;
		}

		if (master.get_digital(DIGITAL_L1) == 1)
		{

			intakeToggle = -1;

		}
		else if (master.get_digital(DIGITAL_L1) == 0)
		{
			rPressed = false;
		}

		//flywheel toggling

		/*
    if (master.get_digital(DIGITAL_R2) == 1 && r2Pressed == false) {
      flyWheelSpeed = flyWheelSpeed + 1;
      r2Pressed = true;
      pros::Task::delay(20);
    } else if (master.get_digital(DIGITAL_R2) == 0) {
      r2Pressed = false;
    }

    if (master.get_digital(DIGITAL_L2) == 1 && l2Pressed == false) {
      flyWheelSpeed = flyWheelSpeed - 1;
      l2Pressed = true;
      pros::Task::delay(20);
    } else if (master.get_digital(DIGITAL_L2) == 0) {
      l2Pressed = false;
    }
		*/

		// pros::lcd::print(2, "ARM: %d",(int)armMotor.get_position()) ;ja
		if (master.get_digital(DIGITAL_R1) == 1)
		{
			changeArm(127);


		}
		else if (master.get_digital(DIGITAL_B)
		 == 1)
		{
			changeArm(-127);

		}
		else
		{
		 armMotor.move_absolute(armMotor.get_position(), 115);
		}


		if (master.get_digital(DIGITAL_UP) == 1)
		{
			motorStop();
		}
		intake(intakeToggle);
		//    flywheel(flyWheelToggle, flyWheelSpeed);
		drive(driveLeft, driveRight);
		reaper(reaperToggle);

		prevTravelDist = frontLeftMtr.get_position();

		pros::lcd::print(1, "RPR: %f INT: %d FLY: %f FLYTARG: %d", reaperMotor.get_actual_velocity(), (int) intakeToggle, (flyWheelMotor.get_actual_velocity()), flyWheelSpeed);
		pros::lcd::print(2, "BL: %lf FL: %lf", backLeftMtr.get_actual_velocity(), frontLeftMtr.get_actual_velocity());
		pros::lcd::print(3, "BR: %lf FR: %lf", backRightMtr.get_actual_velocity(), frontRightMtr.get_actual_velocity());
		pros::lcd::print(5, "READ %d", linesens.get_value());

		//pros::lcd::print(4, "MTRDISP: %lf ", disp);

		if (backLeftMtr.get_actual_velocity() != frontLeftMtr.get_actual_velocity() || backRightMtr.get_actual_velocity() != frontRightMtr.get_actual_velocity())
		{
			printf("MOTOR DISPUTE | ");
			printf(" BL %lf FL %lf |\n", backLeftMtr.get_actual_velocity(), frontLeftMtr.get_actual_velocity());
			printf(" BR %lf FR %lf |\n", backRightMtr.get_actual_velocity(), frontRightMtr.get_actual_velocity());
		}

		//pros::lcd::print(3, "GYRO: %d", (gyroscope.get_value()));
		master.print(1, 0, "Flywheel: %f", getflywheelspeed());

		pros::Task::delay(20);

	}


}
