
#include "LaserGun.h"

/* LASER TAG GUN IMPLEMENTATION
*/

// Trigger with button debounce
bool trigger(laser_gun_t& l)
{
    if ((l.bd.lastTime + c_debounceTime) > millis())
    {
        return;
    }
    l.bd.lastTime = millis();
    l.bd.currentState = digitalRead(l.trigger);

    bool f = false;
    if (l.bd.currentState ==  l.bd.previousState)
    {
        if (l.bd.pressed == HIGH && l.bd.currentState == HIGH)
        {
            if (!l.bd.justPressed)
            {
                l.bd.justPressed = 1;
                f = fire(l);
            }
        }
        l.bd.pressed = !l.bd.currentState;
    }
    l.bd.previousState = l.bd.currentState;
    return f;
}

// Fire function for sending an IR signal
bool fire(laser_gun_t& l)
{
    bool f = false;
    if (canFire(l))
    {
        unsigned long msg = 0;
        msg = (((unsigned long) l.team) << 24) | (((unsigned long) l.player_num) << 16);
        msg = (msg | checksum(msg));

        digitalWrite(l.laser, HIGH);
        l.send.sendNEC(msg, nbits);
        f = true;
    }
    else
    {
        // Play click sound
    }

    triggerRelease(l);
    return f;
}

// Communication with the vest to check if we can fire
bool canFire(laser_gun_t& l)
{
    return digitalRead(l.vest_com) == HIGH;
}

// Release the trigger
void triggerRelease(laser_gun_t& l)
{
    if (l.bd.justPressed == 1)
    {
        l.bd.justPressed = 0;
        digitalWrite(l.laser, LOW);
    }
}