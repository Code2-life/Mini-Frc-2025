#include <Alfredo_NoU2.h>
#include <PestoLink-Receive.h>

//initialize the motors and servos (use custom names)
NoU_Motor left_frontmotr(1);
NoU_Motor left_rearmotr(2);
NoU_Motor right_frontmotr(3);
NoU_Motor right_rearmotr(4);
NoU_Motor star_motr(5);

NoU_Drivetrain drivetrain(&left_frontmotr, &left_rearmotr, &right_frontmotr, &right_rearmotr);
//Servos
NoU_Servo swivel_servo(1);
NoU_Servo claw_servo(2);


// initial angle
int claw_initial = 180;




void setup() {
    PestoLink.begin("Test_BLT")
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
    int servoangle_1 = 0;
    int servoangle_2 = 0;
    int rotation = 0;
    int throttle = 0;


    if (PestoLink.isConnected()) {
        float throttle = -PestoLink.getAxis(1);
        float rotation = PestoLink.getAxis(2);


        drivetrain.arcadeDrive(throttle, rotation);

        RSL::setState(RSL_ENABLED);

    }
    else {
        RSL::setState(RSL_DISABLED);
        
    }

    if (PestoLink.buttonHeld(0)) {  // Button A
        servoangle_1 = 90;
    }
    else (
        servoangle_1 = 0;
    )

     if (PestoLink.buttonHeld(1)) { // Button B
        servoangle_2 = 180;
    }
    else (
        servoangle_2 = 0;
    )

    swivel_servo.write(servoangle_1);
    claw_servo.write(servoangle_2);

    RSL::update();    
    
}