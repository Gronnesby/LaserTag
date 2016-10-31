
#include "LaserGun.h"

/* LASER TAG GUN IMPLEMENTATION
 */

buttonDebounce_t m_debounce;

void triggerRelease()
{
    if (m_debounce.justPressed == 1)
    {
        m_debounce.justPressed = 0;
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
    m_debounce.currentState = digitalRead(m_triggerPin);

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
        man.transmit(m_playerNumber);
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

void LaserGun::isDead()
{

}
