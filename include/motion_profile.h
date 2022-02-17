//constructors
struct Acceleration;

//control
int accelerate();
int decelerate();
int driveProfile (int dist, double maxspeed, bool fwd);
int driveProfileslow(int dist, bool fwd);
int test2();