#include <Servo.h> 

// Middle Controller
Servo middle;                   // Define middle servo
int servo_middle_pin = 11;      // Define Servo pin
int middle_angle;               // Define Servo angle
int middle_joystick_pin = A0;   // Define JoyStick Pin

// Left Controller
Servo left;
int servo_left_pin = 10;
int lef_angle;
int left_joystick_pin = A1;

// Right Controller
Servo right;
int servo_right_pin = 9;
int right_angle;
int right_joystick_pin = A2;

// Claw Controller
Servo claw ;
int servo_claw_pin = 5;
int claw_angle;
int claw_joystick_pin = A3;


// ************************** //
int JOYSTICK_MOVE_FORWARD = 95;
int JOYSTICK_MOVE_BACKWARD = 85;
int SERVO_ANGLE_MAX = 180;
int SERVO_ANGLE_MIN = 0;
const int SERVO_STEP = 1;
const int DELAY_TIME = 20;

void setup() 
{ 
  Serial.begin(9600);
  init_controllers();
}

void init_controllers() {
  init_controller(middle, servo_middle_pin, middle_joystick_pin);
  init_controller(left,   servo_left_pin,   left_joystick_pin);
  init_controller(right,  servo_right_pin,  right_joystick_pin);
  init_controller(claw,   servo_claw_pin,   claw_joystick_pin);
}

void init_controller(Servo servo, int servo_pin, int joystick_pin) {
  servo.attach(servo_pin, 500, 2400);
  pinMode(joystick_pin, INPUT);
}

void get_current_servo_angle() {
  middle_angle = middle.read();
  lef_angle = left.read();
  right_angle = right.read();
  claw_angle = claw.read();
}


void loop() 
{ 
  get_current_servo_angle();

  move_servo(middle, get_joystick_mapped_value(middle_joystick_pin), middle_angle);
  move_servo(left, get_joystick_mapped_value(left_joystick_pin), lef_angle);
  move_servo(right, get_joystick_mapped_value(right_joystick_pin), right_angle);
  move_servo(claw, get_joystick_mapped_value(claw_joystick_pin), claw_angle);
  
  delay(DELAY_TIME);
} 

int get_joystick_mapped_value(int joystick) {
  return map(analogRead(joystick), 0, 1023, 0, 180);
}

void move_servo(Servo target_servo, int joystick_mapped_value, int servo_angle) {
  if (joystick_mapped_value > JOYSTICK_MOVE_FORWARD) {
    servo_angle += SERVO_STEP;
    if (servo_angle > SERVO_ANGLE_MAX) {
      servo_angle = SERVO_ANGLE_MAX;
    }
  }
  else if (joystick_mapped_value < JOYSTICK_MOVE_BACKWARD) {
    servo_angle -= SERVO_STEP;
    if (servo_angle <= SERVO_ANGLE_MIN) {
      servo_angle = SERVO_ANGLE_MIN;
    }
  }
  target_servo.write(servo_angle);
}
