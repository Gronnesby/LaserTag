
#include "LaserGun.h"

/* LASER TAG GUN IMPLEMENTATION
*/

void LaserGun::triggerRelease()
{
    if (m_debounce.justPressed == 1)
    {
        m_debounce.justPressed = 0;
        digitalWrite(m_laserpin, LOW);
    }
}


/* Debounce method for the guns trigger.
 * This method should either directly call fire,
 * or trigger an interrupt that fire is attached to.
 */
void LaserGun::trigger()
{
    if ((m_debounce.lastTime + c_debounceTime) > millis())
    {
        return;
    }
    m_debounce.lastTime = millis();
    m_debounce.currentState = digitalRead(m_triggerpin);

    if (m_debounce.currentState ==  m_debounce.previousState)
    {
        if (m_debounce.pressed == HIGH && m_debounce.currentState == HIGH)
        {
            if (!m_debounce.justPressed)
            {
                m_debounce.justPressed = 1;
                fire();
            }
        }
        m_debounce.pressed = !m_debounce.currentState;
    }
    m_debounce.previousState = m_debounce.currentState;
}


/* Fire method for the gun.
 * Trigger should either call this to fire,
 * or this could be an event handler invoked by an interrupt.
 */
void LaserGun::fire()
{
    if (canFire())
    {
        unsigned long msg = 0;
        msg = (((unsigned long) m_team) << 24) | (((unsigned long) m_playernum) << 16);
        msg = (msg | checksum(msg));

        Serial.println(msg, HEX);

        digitalWrite(m_laserpin, HIGH);
        m_irsend.sendSony(msg, nbits);
    }
    else
    {
        // Play click sound
    }

    triggerRelease();
}

/* Communicates with the vest and checks wether
 * the gun can fire or not.
 */
bool LaserGun::canFire()
{
    return true; //(digitalRead(m_comPin) == HIGH);
}

unsigned long checksum(unsigned long msg)
{
    unsigned long team = (msg >> 24);
    unsigned long plnum = (msg & 0x00FF0000) >> 16;

    unsigned long chksum = (team + plnum) % 255;

    return chksum;
}
