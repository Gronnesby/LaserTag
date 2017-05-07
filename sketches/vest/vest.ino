
#include <LaserVest.h>

#define NUMLEDS 17

int ledpin = 13;
int ledstate = HIGH;
int team = TEAM_A;

IRrecv ir = IRrecv(9);
decode_results res;

LaserVest vest = LaserVest(23, team, 10);

void setup(void)
{
    ir.enableIRIn();
    pinMode(ledpin, OUTPUT);
    digitalWrite(ledpin, ledstate);
   
    delay(10);
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
            ir.resume();
        }
    }
    else
    {
        vest.lockout();
    }
    delay(10);
}


void decode_ir_msg(unsigned long val)
{
    
}