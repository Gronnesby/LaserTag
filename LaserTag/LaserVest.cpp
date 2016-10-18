

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 * Constructor for the Laser Vest class
 */
LaserVest::LaserVest(unsigned char playerNumber, unsigned int gunComPin)
{
    m_comPin = gunComPin;
    m_playerNumber = playerNumber;
    digitalWrite(m_comPin, HIGH);
}


void LaserVest::disableWeapon()
{
    digitalWrite(m_comPin, LOW);
}
