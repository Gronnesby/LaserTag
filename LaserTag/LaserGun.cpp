
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
        if (m_debounce.pressed == LOW && m_debounce.currentState == LOW)
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
        msg = (((unsigned long) m_team) << 16) | ((unsigned long) m_playernum);
        Serial.println(msg, BIN);
        Serial.println(sizeof(long));
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
