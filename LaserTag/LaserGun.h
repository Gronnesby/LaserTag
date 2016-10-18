#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"

class LaserGun : public LaserEquipment
{
    public:
        LaserGun(unsigned char player_number, unsigned int triggerPin);
        void trigger();

    private:
        void fire();
        bool canFire();
        const unsigned int m_triggerPin;
};


#endif
