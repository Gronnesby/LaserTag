#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"

const int lockoutMillis = 6000;

class LaserVest
{
    public:
        // Constructor
        LaserVest(int playernum, int team, int compin):
        m_playernum(playernum),
        m_compin(compin),
        m_team(team)
        {
            pinMode(m_compin, OUTPUT);
            digitalWrite(m_compin, HIGH);
            
            alive = true;
            m_ledState = HIGH;
            m_tod = 0;
            m_ledTimer = 0;
            m_score = 0;

        }


        void lockout();

        // Decode the message received via IR
        void decodeMessage(unsigned long val);

        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        bool alive;

    private:

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();

        void blinkLeds();

        unsigned int m_playernum;
        int m_compin;
        int m_sensorpin;

        long m_tod;
        long m_ledTimer;
        int m_ledState;

        uint16_t m_team;
        uint32_t m_teamColor;
        unsigned int m_score;
};

#endif
