
#include <LaserGun.h>

int playernum = 23;
int compin = 9;
int trigger = 5;
int fire = 3;
int laser = 4;

LaserGun gun(playernum, compin, trigger, fire, laser);

int leds = 13;

void setup()
{
  pinMode(leds, OUTPUT);
  digitalWrite(leds, HIGH);
}

void loop()
{
    if (gun.trigger())
    {
        blink_leds();
    }
}

void blink_leds()
{
    digitalWrite(leds, LOW);
    delay(20);
    digitalWrite(leds, HIGH);
    delay(20);
    digitalWrite(leds, LOW);
    delay(20);
    digitalWrite(leds, HIGH);
}
