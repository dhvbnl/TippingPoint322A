//constants
const int tBondRearLift = 11;
const int bBondRearLift = 40;


int liftControl();

void setFourBarSpeed(double speed);
void setFourBarSpeedHolding(double speed);
void setFourBarPosition(int pos);
void setFourBarIntakeAuton();

void changeArmPos(int pos);
void fourBarGround();
void fourBarRing();
void fourBarSeasaw();

void setRearClamp();
void setFrontClamp();
void setGoalCover();

void setRearClampAuton();
void setFrontClampAuton();
void setGoalCoverAuton();

void rearClampCheck();

void setIntakeSpeed();
void intakeMove(int start);

int getFourBarSpeed();
int getFourBarPos();

bool buttonPressed();

int getFourBarPot();
int getFourBarCurPos();

void findBottomBound();