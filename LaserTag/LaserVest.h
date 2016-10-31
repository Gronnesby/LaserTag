#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"


class LaserVest : public LaserEquipment
{
    public:
        // Constructor and parent object initialization.
        LaserVest(uint playernum, uint comPin, ulong gracePeriod, uint sensorPin) : LaserEquipment(playernum, comPin),
        m_deathTimePenalty(gracePeriod),
        m_sensorPin(sensorPin)
        {
            pinMode(sensorPin, INPUT);
            digitalWrite(m_comPin, HIGH);
            man.setupReceive(sensorPin, MAN_300);
            man.beginReceive();
        }

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();

        // Receives a message over the registered sensorpin
        uint16_t receive();

    private:
        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        ulong m_deathTimePenalty;
        Status m_weaponStatus;
        uint m_sensorPin;
};

#endif
