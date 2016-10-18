#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"

class LaserVest : public LaserEquipment
{
    public:
        LaserVest(unsigned char playerNumber);
        void disableWeapon();

    private:
        void enableWeapon();
        const unsigned long m_deathTimePenalty;
};

#endif
