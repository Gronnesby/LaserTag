

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */


/* Disable the weapon by writing LOW to the communcation pin.
 */
void disableWeapon(laser_vest_t &v)
{
    digitalWrite(v.to_gun, LOW);
}


/* Enable the weapon by writing HIGH to the communcation pin.
 */
void enableWeapon(laser_vest_t &v)
{
    digitalWrite(v.to_gun, HIGH);
}

void sendSignal(laser_vest_t &v)
{
    unsigned long flash_msg = 0;
    flash_msg = flash_msg | (((unsigned long) COMMAND) << 24) | (((unsigned long) v.player_num) << 16) | (((unsigned long) v.shot_by) << 8);
    flash_msg = (flash_msg | checksum(flash_msg));

    v.send.sendNEC(flash_msg, 32);
}


void decodeMessage(laser_vest_t &v)
{
    unsigned long val = v.results.value;
    unsigned long plnum = 0;
    unsigned long t = 0;
    unsigned long chk = 0;

    t = (val >> 24);
    plnum = (val & 0x00FF0000) >> 16;
    chk = (val & 0x000000FF);

    if(chk != checksum(val))
    {
        // Ignore corrupted values
        return;
    }
    else
    {
        if(t != v.team && t != COMMAND)
        {
            v.alive = false;
            v.tod = millis();
            v.blink_timer = millis();
            return;
        }
        else if (t == COMMAND)
        {
            unsigned int target = (val & 0x0000FF00) >> 8;
            if (target == v.player_num)
            {
                v.score++;
            }
        }
    }
}


void blinkLeds(laser_vest_t &v)
{
    if((millis() - v.blink_timer) >= 300)
    {
        v.blink_timer = millis();

        if (v.ledstate == HIGH)
        {
            setStripColor(v, 0xFF000000);
            v.ledstate = LOW;
            digitalWrite(v.white_leds, v.ledstate);
        }
        else
        {
            setStripColor(v, v.teamcolor);
            v.ledstate = HIGH;
            digitalWrite(v.white_leds, v.ledstate);
        }
        v.strip.show();
    }
}

void setStripColor(laser_vest_t &v, uint32_t col)
{
        for(int i = 0; i < v.npixels; i++)
        {
            v.strip.setPixelColor(i, col);
        }
        v.strip.show();
}