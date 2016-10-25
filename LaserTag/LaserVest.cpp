

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

    if (man.receiveComplete())
    {

    }
    return 0;
}
