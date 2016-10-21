#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"



class LaserVest : public LaserEquipment
{
    public:
        LaserVest(uint playernum, uint comPin, ulong gracePeriod)
        : LaserEquipment(playernum, comPin),
        m_deathTimePenalty(gracePeriod)
        {
            digitalWrite(m_comPin, HIGH);
        }
        void disableWeapon();

    private:
        void enableWeapon();
        ulong m_deathTimePenalty;
};

#endif
