
#include <LaserGun.h>

LaserGun gun(23, 1, 2, 3, 5);

void setup()
{
  Serial.begin(9600);
}


void loop()
{
    gun.trigger();
}
