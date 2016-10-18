
#include "LaserGun.h"


/* LASER TAG GUN IMPLEMENTATION
 * Constructor for the Laser Gun class
 */
LaserGun::LaserGun(unsigned char player_number, unsigned int triggerPin, unsigned int vestComPin)
{
    m_playerNumber = playerNumber;
    m_comPin = vestComPin;
    m_triggerPin = triggerPin;
}

/* Method for playing a sound from the gun.
 *
 */
void LaserGun::playSound(Sound s)
{
    switch(s)
    {
        case FIRE:
            // Play a fire sound
            break;
        case CLICK:
            // Play a click sound
            break;
        default:
            break;
    }
}

/* Debounce method for the guns trigger.
 * This method should either directly call fire,
 * or trigger an interrupt that fire is attached to.
 */
void LaserGun::trigger()
{

}


/* Fire method for the gun.
 * Trigger should either call this to fire,
 * or this could be an event handler invoked by an interrupt.
 */
void LaserGun::fire()
{
    if (canFire())
    {
        // Fire the laser OR invoke interrupt to fire the gun

        playSound(FIRE);
    }
    else
    {
        // Just play a click sound
        playSound(CLICK);
    }
}

/* Communicates with the vest and checks wether
 * the gun can fire or not.
 */
bool LaserGun::canFire()
{
    return (digitalRead(m_comPin) == HIGH)
}
