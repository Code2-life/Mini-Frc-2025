from math import *


m_ang = 32.8
ang_s = (5.0*2.0*3.14)/m_ang

print ("anglar scale:", ang_s)


while True: 
    a = float(input("enter x:"))
    b = float(input("enter y:"))
    rotation= float(input("enter rotation:"))
    yaw = float(input("enter yaw:"))

    botHeading = yaw
    print (f"angle of the robot: {botHeading}")

    rotX = a * cos(-botHeading) - b * sin(-botHeading)
    rotY = a * sin(-botHeading) + b * cos(-botHeading)


    print (f" transformed x and y; {rotX}, {rotY}")
    calc = fabs(rotY) + fabs(rotX) + fabs(rotation)

    if (calc >= 1):
        denom = calc
    else:
        denom =1
        
    print (f"denominator: {denom}")
    
    frontLeftPower  = (rotY + rotX + rotation) / denom
    backLeftPower   = (rotY - rotX + rotation) / denom
    frontRightPower = (rotY - rotX - rotation) / denom
    backRightPower  = (rotY + rotX - rotation) / denom
    
    print (f"Powers: {frontLeftPower}, {backLeftPower}, {frontRightPower}, {backRightPower}")