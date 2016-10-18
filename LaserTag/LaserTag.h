#ifndef __LASER_TAG_H__
#define __LASER_TAG_H__

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
    #include "pins_arduino.h"
    #include "WConstants.h"
#endif

enum Sound : unsigned char
{
    FIRE,
    CLICK,
    SHOT
};

class LaserEquipment
{
    public:
        void playSound(Sound s);

    private:
        const unsigned char m_playerNumber;
        const unsigned int m_comPin;
};

#endif
