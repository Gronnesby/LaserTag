
#include <LaserVest.h>

// LaserVest object, Args: int playernum, int compin, long graceperiod, int sensorpin
LaserVest vest(23, TEAM_B, 1, 5);

void setup(void)
{
    Serial.begin(9600);
}


void loop(void)
{
  vest.receive();
}
