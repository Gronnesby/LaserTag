#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"
#include "Manchester.h"

const long c_deltaSendTime = 120;
const long c_debounceTime = 10;

struct buttonDebounce
{
    byte previousState;
    byte currentState;
    ulong lastTime;

    byte pressed;
    byte hold;
    volatile byte justPressed;
    volatile byte justReleased;
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
            man.setupTransmit(firePin, MAN_300);
        }
        void trigger();

    private:
        void fire();
        bool canFire();
        void isDead();

        uint m_triggerPin;
        uint m_firePin;
        Manchester man;
};


#endif
