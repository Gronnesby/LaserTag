#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"


class LaserVest : public LaserEquipment
{
    public:
        // Constructor and parent object initialization.
        LaserVest(int playernum, int comPin, int sensorPin) : LaserEquipment(playernum, comPin),
        m_irrecv(sensorPin)
        {
            digitalWrite(m_comPin, HIGH);
            m_upgrades = NONE;
            m_irrecv.enableIRIn();
        }

        // Receives a message over the registered sensorpin
        uint32_t receive();

    private:

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();

        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        void applyStatus(uint16_t options);

        int m_sensorPin;
        uint16_t m_upgrades;
        IRrecv m_irrecv;
};

#endif
