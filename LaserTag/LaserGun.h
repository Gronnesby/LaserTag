#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"

const long c_debounceTime = 10;

struct buttonDebounce
{
    byte previousState;
    byte currentState;
    ulong lastTime;

    byte pressed;
    byte hold;
    byte justPressed;
    byte justReleased;
};
typedef struct buttonDebounce buttonDebounce_t;

class LaserGun : public LaserEquipment
{
    public:
        LaserGun(uint playernum, uint comPin, uint triggerPin, uint firePin)
        : LaserEquipment(playernum, comPin),
        m_triggerPin(triggerPin),
        m_firePin(firePin)
        {
            pinMode(triggerPin, INPUT);
            pinMode(firePin, OUTPUT);
        }
        void trigger();

    private:
        void fire();
        bool canFire();
        void isDead();

        uint m_triggerPin;
        uint m_firePin;
        buttonDebounce_t m_debounce;

};


#endif
