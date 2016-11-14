

#include "LaserVest.h"

/* LASER TAG VEST IMPLEMENTATION
 */

 void LaserVest::receive()
{

      unsigned long val = 0;
      unsigned long plnum = 0;
      unsigned long upgrd = 0;

      if (m_irrecv.decode(&m_res)) {
        val = m_res.value;
        Serial.println(val, BIN);
        upgrd = (val >> 16);
        plnum = (val & 0x0000FFFF);
        Serial.println(upgrd, DEC);
        Serial.println(plnum, DEC);
        m_irrecv.resume(); // Receive the next value
      }
      delay(10);
}

/* Disable the weapon by writing LOW to the communcation pin.
 */
void LaserVest::disableWeapon()
{
    digitalWrite(m_compin, LOW);

    // Should probably set up a enable weapon timed interrupt here
    // Or at least count down in the receive method
}


/* Enable the weapon by writing HIGH to the communcation pin.
 */
void LaserVest::enableWeapon()
{
    digitalWrite(m_compin, HIGH);
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
