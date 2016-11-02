#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"


// Global constants
const long c_debounceTime = 10;

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

class LaserGun : public LaserEquipment
{
    public:
        LaserGun(int playernum, int comPin, int triggerPin, int firePin)
        : LaserEquipment(playernum, comPin),
        m_triggerPin(triggerPin),
        m_firePin(firePin)
        {
            pinMode(triggerPin, INPUT);
            pinMode(firePin, OUTPUT);
        }
        // Trigger function with button debouncing
        void trigger();

    private:

        // Fire function for sending an IR signal
        void fire();

        // Communication with the vest to check if we can fire
        bool canFire();

        uint16_t getUpgrades();

        int m_triggerPin;
        int m_firePin;
        uint16_t upgrades;
        IRsend irsend;
};


#endif
