#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"
#include "Manchester.h"


class LaserVest : public LaserEquipment
{
    public:
        LaserVest(uint playernum, uint comPin, ulong gracePeriod, uint sensorPin)
        : LaserEquipment(playernum, comPin),
        m_deathTimePenalty(gracePeriod),
        m_sensorPin(sensorPin)
        {
            pinMode(sensorPin, INPUT);
            digitalWrite(m_comPin, HIGH);
            man.setupReceive(sensorPin);
            man.beginReceiveArray(2, buf);
        }
        void disableWeapon();
        int receive();

    private:
        void enableWeapon();
        uint8_t buf[2];
        ulong m_deathTimePenalty;
        uint m_sensorPin;
        Manchester man;
};

#endif
