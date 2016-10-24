#ifndef __LASER_TAG_H__
#define __LASER_TAG_H__

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
    #include "pins_arduino.h"
    #include "WConstants.h"
#endif

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;


enum Sound : byte
{
    FIRE,
    CLICK,
    SHOT
};

class LaserEquipment
{
    public:
        LaserEquipment(uint playernum, uint comPin)
        {
          m_playerNumber = playernum;
          m_comPin = comPin;
        }
        void playSound(Sound s);

    protected:
        uint16_t m_playerNumber;
        uint m_comPin;
};

#endif
