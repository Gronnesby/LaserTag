

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */


/* Disable the weapon by writing low to the communcation pin.
 */
void LaserVest::disableWeapon()
{
    digitalWrite(m_comPin, LOW);
}

uint16_t LaserVest::receive()
{
    if (man.receiveComplete())
    {
        // Get the message
        uint16_t m = man.getMessage();
        Serial.println(m);
        // Begin listening for next message
        man.beginReceive();

        // Return the message
        return m;
    }
    return 0;
}
