struct Coordinate;

//setters
int setPos(double x, double y, double speed, bool fwd);

//getters
int getPosition();
int getPos();
double getyPos();
double getxPos();
void horizontalmove();
void stopdrive();
void drivetrainTurn(double targetdeg);
void turnNoPid(double deg);

//debug
void printPos();
void hi();

void printinertial();
void arcturn (double left, double right, double turnangle);