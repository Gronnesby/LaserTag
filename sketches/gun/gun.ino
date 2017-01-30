
#include <LaserGun.h>
#include <avr/pgmspace.h>
#include "laser.raw.h"

int playernum = 23;
int compin = 9;
int trigger = 5;
int fire = 3;
int laser = 4;

LaserGun gun(playernum, compin, trigger, fire, laser);

int leds = 13;
int speaker = A0;

const int audio_length = 4135;

void setup()
{
  pinMode(leds, OUTPUT);
  pinMode(speaker, OUTPUT);
  digitalWrite(leds, HIGH);
}

void loop()
{
    if (gun.trigger())
    {
        play_sound();
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

void play_sound()
{
}
