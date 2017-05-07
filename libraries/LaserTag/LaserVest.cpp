

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */


/* Disable the weapon by writing LOW to the communcation pin.
 */
void LaserVest::disableWeapon()
{
    digitalWrite(m_compin, LOW);
}


/* Enable the weapon by writing HIGH to the communcation pin.
 */
void LaserVest::enableWeapon()
{
    digitalWrite(m_compin, HIGH);
}


void LaserVest::decodeMessage(unsigned long val)
{
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
        if(t != m_team && t != COMMAND)
        {
            alive = false;
            m_tod = millis();
            m_ledTimer = millis();
            return;
        }
        else if (t == COMMAND)
        {
            unsigned int target = (val & 0x0000FF00) >> 8;
            if (target == m_playernum)
            {
                m_score++;
            }
        }
    }
}

void LaserVest::lockout()
{
    disableWeapon();
    if ((m_tod > 0) && ((millis() - m_tod) > lockoutMillis))
    {
        alive = true;
        m_tod = 0;
        m_ledState = HIGH;
        
    }
    else
    {
        blinkLeds();
    }
}


void LaserVest::blinkLeds()
{
    if((millis() - m_ledTimer) >= 300)
    {
        m_ledTimer = millis();
        if (m_ledState == HIGH)
        {
            m_ledState = LOW;
        }
        else
        {
            m_ledState = HIGH;
        }
    }
}