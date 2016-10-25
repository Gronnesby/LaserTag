#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"
#include "Manchester.h"


enum

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
            man.setupReceive(sensorPin);
            man.beginReceive();
        }

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();

        // Receives a message over the registered sensorpin
        int receive();

    private:
        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        ulong m_deathTimePenalty;
        Status m_weaponStatus;
        uint m_sensorPin;
        Manchester man;
};

#endif
