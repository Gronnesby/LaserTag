#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"


// Global constants
const long c_debounceTime = 10;
const int nbits = sizeof(unsigned long) * 8;


struct buttonDebounce
{
    byte previousState;
    byte currentState;
    long lastTime;

    byte pressed;
    byte hold;
    volatile byte justPressed;
    volatile byte justReleased;
};
typedef struct buttonDebounce buttonDebounce_t;

class LaserGun
{
    public:
        LaserGun(int playernum, int compin, int triggerpin, int firepin, int laserpin) :
        m_playernum(playernum),
        m_triggerpin(triggerpin),
        m_firepin(firepin),
        m_compin(compin),
        m_laserpin(laserpin),
        m_irsend(IRsend())
        {
            m_upgrades = NONE;
            m_team = TEAM_A;

            m_debounce = buttonDebounce_t{};

            pinMode(m_triggerpin, INPUT);
            //pinMode(m_firepin, OUTPUT);
            pinMode(m_laserpin, OUTPUT);

        }
        // Trigger function with button debouncing
        void trigger();

    private:

        // Fire function for sending an IR signal
        void fire();

        // Communication with the vest to check if we can fire
        bool canFire();

        // Release the trigger
        void triggerRelease();

        uint16_t getUpgrades();

        int m_triggerpin;
        int m_firepin;
        int m_compin;
        int m_laserpin;

        buttonDebounce_t m_debounce;

        uint8_t m_playernum;
        uint8_t m_team;
        uint16_t m_upgrades;
        IRsend m_irsend;
};

unsigned long checksum(unsigned long msg);

#endif
