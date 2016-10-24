

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */


/* Disable the weapon by writing low to the communcation pin.
 */
void LaserVest::disableWeapon()
{
    digitalWrite(m_comPin, LOW);
}

int LaserVest::receive()
{
    if(man.receiveComplete())
    {
        Serial.println(buf[0]);
        uint16_t msg = 0;
        msg |= (buf[0] << 8);
        msg |= buf[1];
        return msg;
    }

    return 0;
}
