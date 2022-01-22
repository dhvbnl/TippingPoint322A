//constants
const int tBondRearLift = 11;
const int bBondRearLift = 40;

int liftControl();

void setRearLiftSpeed(int speed);
void setRearCascadeSpeed(int speed);
void setFrontSixBarSpeed(int speed);

void setRearLiftBrake();

int getRearLiftSpeed();
int getFrontSixBarSpeed();
int getRearCascadeSpeed();

int getlFrontDriveVoltage();
int getBackLiftPot();