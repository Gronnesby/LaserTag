
#include <LaserVest.h>
#include <Adafruit_NeoPixel.h>


int ledpin = 13;
int ledstate = HIGH;

IRrecv ir = IRrecv(9);
decode_results res;

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, STRIPPIN, NEO_GRB + NEO_KHZ800);
LaserVest vest = LaserVest(23, TEAM_B, 10, 9, ir, res);

void setup(void)
{
    Serial.begin(9600);

    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, ledstate);
    
    Serial.println("Setup");
}


void loop(void)
{
    if (vest.alive)
    {
        vest.enableWeapon();
        if (ir.decode(&res))
        {
            unsigned long val = res.value;
            vest.decodeMessage(val);
        }
    }
    else
    {
        vest.lockout();
    }
}
