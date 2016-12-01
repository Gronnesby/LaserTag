
#include <LaserGun.h>

LaserGun gun(23, 9, 5, 3, 4);

void setup()
{
  Serial.begin(9600);
}


void loop()
{
    gun.trigger();
}
