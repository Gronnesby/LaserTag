#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"




class LaserVest
{
    public:
        // Constructor
        LaserVest(int playernum, int team, int compin, int sensorpin):
        m_playernum(playernum),
        m_compin(compin),
        m_sensorpin(sensorpin),
        m_team(team),
        m_irrecv(m_sensorpin)
        {
            digitalWrite(m_compin, HIGH);
            m_upgrades = 0x0;
            m_irrecv.enableIRIn();
        }

        // Receives a message over the registered sensorpin
        void receive();

    private:

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();

        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        void applyStatus(uint16_t options);

        int m_playernum;
        int m_compin;
        int m_sensorpin;

        uint16_t m_upgrades;
        uint16_t m_team;

        decode_results m_res;
        IRrecv m_irrecv;
};

#endif
