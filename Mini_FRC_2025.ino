#include <Alfredo_NoU2.h>
#include <PestoLink-Receive.h>

//initialize the motors and servos (use custom names)
NoU_Motor left_frontmotr(1);
NoU_Motor left_rearmotr(2);
NoU_Motor right_frontmotr(3);
NoU_Motor right_rearmotr(4);
NoU_Motor starmotr(5);

NoU_Drivetrain drivetrain(&left_frontmotr, &left_rearmotr, &right_frontmotr, &right_rearmotr);
//Servos
NoU_Servo swivel_servo(1);
NoU_Servo claw_servo(2);


// initial angle
int claw_initial = 180;

int servoangle_1;
int servoangle_2;
float x;
float y;
float rot;

void setup() {
    PestoLink.begin("Test_BLT"); //name of broadcast
    Serial.begin(115200); //speed at which data is exchanged with ESP32 (dont change)
                                    
    left_frontmotr.setInverted(false); 
    right_frontmotr.setInverted(false);  
    left_rearmotr.setInverted(false);
    right_rearmotr.setInverted(false);
    starmotr.setInverted(false);



    RSL::initialize(); //Initialize Robot Signal Light system (dont change)
    RSL::setState(RSL_ENABLED); //Enable it
}

void loop() {
    servoangle_1 = 0;
    servoangle_2 = 0;


    if (PestoLink.isConnected()) {
        x = PestoLink.getAxis(1); //setting the input parameters based on joystick
        y = -PestoLink.getAxis(0);
        rot = PestoLink.getAxis(3);


        drivetrain.holonomicDrive(x, y, rot); //Does all the math nothin else needed




        RSL::setState(RSL_ENABLED); //no need to change

    }
    else {
        RSL::setState(RSL_DISABLED); //no need to change
        
    }



/////////////////////////////////////////////////////////////////////////////////////////////////////



    if (PestoLink.buttonHeld(0)) {  // Button A
        servoangle_1 = 90;
    }
    else {
        servoangle_1 = 0;
    }

    if (PestoLink.buttonHeld(1)) { // Button B
        servoangle_2 = 180;
    }
    else {
        servoangle_2 = 0;
    }
  
    if (PestoLink.buttonHeld(3)) { //Button X
        starmotr.set(0.5);
    }
    else {
        starmotr.set(0);
    }
    
    swivel_servo.write(servoangle_1);
    claw_servo.write(servoangle_2);

    RSL::update();    
}
