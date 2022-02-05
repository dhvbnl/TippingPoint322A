//constants
const double quadraticA = 0.12;
const int powerRatioB = 1;

//complete functions
void drivetrainControl();

//setters
void setDrivetrainSpeed(int leftSpeed, int rightSpeed);

void setDrivetrainCreep();
void setDrivetrainLock();
void setDrivetrainHold();

//getters
double getLeftSpeedInLinear();
double getRightSpeedInLinear();

int getLeftSpeedInSlew();
int getRightSpeedInSlew();

int getLFrontSpeed();
int getLBackSpeed();
int getRBackSpeed();
int getRFrontSpeed();

double getInertialRotation();
double getInertialHeading();

double getLeftEncoderRotation();
double getRightEncoderRotation();
double getMiddleEncoderRotation();

double getLeftEncoderVelocity();
double getRightEncoderVelocity();
double getMiddleEncoderVelocity();

int getLeftFrontTemp();
int getLeftMiddleTemp();
int getLeftBackTemp();
int getRightFrontTemp();
int getRightMiddleTemp();
int getRightBackTemp();

double getLeftDifference();
double getRightDifference();

//control 
void resetDrivetrain();
void resetEncoders();
void calibrateInertial();
void drivetrainTurn(double targetdeg);
void timeDrive(double speed, int timeLength);
void arcturn (double left, double right, double turnangle);
void arcturnTime (double left, double right, int length);

std::string tempInfoDrive();

