
#include "LaserGun.h"


/* LASER TAG GUN IMPLEMENTATION
 */


/* Debounce method for the guns trigger.
 * This method should either directly call fire,
 * or trigger an interrupt that fire is attached to.
 */
void LaserGun::trigger()
{
    Serial.println(m_debounce.currentState, DEC);
    if ((m_debounce.lastTime + c_debounceTime) > millis())
    {
        return;
    }
    m_debounce.lastTime = millis();

    if (millis() < m_debounce.lastTime)
    {
        m_debounce.lastTime = millis();
    }
    m_debounce.currentState = digitalRead(m_triggerPin);
    Serial.println(m_debounce.currentState, DEC);
    if (m_debounce.currentState ==  m_debounce.previousState)
    {
        if (m_debounce.pressed == LOW && m_debounce.currentState == LOW)
        {
            m_debounce.justPressed = 1;
        }
        else if (m_debounce.pressed == HIGH && m_debounce.currentState == HIGH)
        {
            m_debounce.justReleased = 1;
        }
        m_debounce.pressed = !m_debounce.currentState;
    }

    if (m_debounce.justPressed)
    {
        fire();
    }
}


/* Fire method for the gun.
 * Trigger should either call this to fire,
 * or this could be an event handler invoked by an interrupt.
 */
void LaserGun::fire()
{
    digitalWrite(m_firePin, HIGH);
    delay(150);
    digitalWrite(m_firePin, LOW);


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
