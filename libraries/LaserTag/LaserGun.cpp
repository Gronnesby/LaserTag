
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
 */
bool LaserGun::trigger()
{
    if ((m_debounce.lastTime + c_debounceTime) > millis())
    {
        return;
    }
    m_debounce.lastTime = millis();
    m_debounce.currentState = digitalRead(m_triggerpin);

    bool f = false;
    if (m_debounce.currentState ==  m_debounce.previousState)
    {
        if (m_debounce.pressed == HIGH && m_debounce.currentState == HIGH)
        {
            if (!m_debounce.justPressed)
            {
                m_debounce.justPressed = 1;
                f = fire();
            }
        }
        m_debounce.pressed = !m_debounce.currentState;
    }
    m_debounce.previousState = m_debounce.currentState;
    return f;
}


/* Fire method for the gun.
 * Trigger should either call this to fire,
 * or this could be an event handler invoked by an interrupt.
 */
bool LaserGun::fire()
{
    bool f = false;
    if (canFire())
    {
        unsigned long msg = 0;
        msg = (((unsigned long) m_team) << 24) | (((unsigned long) m_playernum) << 16);
        msg = (msg | checksum(msg));

        digitalWrite(m_laserpin, HIGH);
        m_irsend.sendSony(msg, nbits);
        Serial.println(msg, HEX);
        f = true;
    }
    else
    {
        // Play click sound
    }

    triggerRelease();
    return f;
}

void LaserGun::playSound(int sound)
{

}

void LaserGun::recvIRSignal()
{
    
}

/* Communicates with the vest and checks wether
 * the gun can fire or not.
 */
bool LaserGun::canFire()
{
    return (digitalRead(m_compin) == HIGH);
}


// bool trigger(laser_gun_t& l)
// {
//     buttonDebounce_t m_debounce = l->bd;
//     if ((m_debounce.lastTime + c_debounceTime) > millis())
//     {
//         return;
//     }
//     m_debounce.lastTime = millis();
//     m_debounce.currentState = digitalRead(m_triggerpin);

//     bool f = false;
//     if (m_debounce.currentState ==  m_debounce.previousState)
//     {
//         if (m_debounce.pressed == HIGH && m_debounce.currentState == HIGH)
//         {
//             if (!m_debounce.justPressed)
//             {
//                 m_debounce.justPressed = 1;
//                 f = fire();
//             }
//         }
//         m_debounce.pressed = !m_debounce.currentState;
//     }
//     m_debounce.previousState = m_debounce.currentState;
//     return f;
// }

// // Fire function for sending an IR signal
// bool fire(laser_gun_t& l);

// // Communication with the vest to check if we can fire
// bool canFire(laser_gun_t& l);

// // Release the trigger
// void triggerRelease(laser_gun_t& l);