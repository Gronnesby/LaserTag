
#include "LaserGun.h"

/* LASER TAG GUN IMPLEMENTATION
 */

buttonDebounce_t m_debounce;
TimerOne timer;

void triggerRelease()
{
    if (m_debounce.justPressed == 1)
    {
        m_debounce.justPressed = 0;
    }
}

void LaserGun::sendHeader()
{
    int i, k = 5;
    for (i = 0; i < k; i++)
    {
        digitalWrite(m_firePin, HIGH);
        delayMicroseconds(10000);

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
    long t = millis();
    int i;
    while((millis() - t) < c_deltaSendTime)
    {
        sendHeader();
        for (i = 0; i < 8; i++)
        {
            digitalWrite(m_firePin, ((m_playerNumber >> i) & 0xFF));
            delayMicroseconds(10000);
        }
    }
    digitalWrite(m_firePin, LOW);
    triggerRelease();
}

/* Communicates with the vest and checks wether
 * the gun can fire or not.
 */
bool LaserGun::canFire()
{
    return (digitalRead(m_comPin) == HIGH);
}

void LaserGun::isDead()
{

}
