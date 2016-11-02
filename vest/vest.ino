
#include <LaserVest.h>


// LaserVest object, Args: int playernum, int compin, long graceperiod, int sensorpin
LaserVest vest(23, 1, 3);

void setup(void)
{
    Serial.begin(9600);
}


void loop(void)
{

    uint32_t sig = vest.receive();
    if (sig)
    {
        Serial.println(sig);
    }

}
