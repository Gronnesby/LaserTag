

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */




uint32_t LaserVest::receive()
{
    decode_results results;
    if (m_irrecv.decode(&results))
    {
        uint16_t playernum = results.value & PLAYER_MASK;
        uint16_t statuscode = (results.value & STATUS_MASK) >> 16;

        applyStatus(statuscode);

        return results.value;
    }

    return 0;
}

/* Disable the weapon by writing LOW to the communcation pin.
 */
void LaserVest::disableWeapon()
{
    digitalWrite(m_comPin, LOW);

    // Should probably set up a enable weapon timed interrupt here
    // Or at least count down in the receive method
}


/* Enable the weapon by writing HIGH to the communcation pin.
 */
void LaserVest::enableWeapon()
{
    digitalWrite(m_comPin, HIGH);
}


void LaserVest::applyStatus(uint16_t options)
{

    if (((options & TEAM_A) != m_team) || ((options & TEAM_B) != m_team))
    {
        // Got shot by the other team, do something here
        disableWeapon();
    }
    else if (((options & TEAM_A) == m_team) || ((options & TEAM_B)== m_team))
    {
        // Friendly fire
    }

    if (options & UPGRADES)
    {
        if (!(m_upgrades & UPGRADES))
        {
            m_upgrades |= (options & UPGRADE_RAPID);
            m_upgrades |= (options & UPGRADE_INVULN);
            m_upgrades |= (options & UPGRADE_INVIS);
            m_upgrades |= (options & UPGRADE_SPY);
        }
    }

}
