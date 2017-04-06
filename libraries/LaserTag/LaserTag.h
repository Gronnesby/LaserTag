#ifndef __LASER_TAG_H__
#define __LASER_TAG_H__

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
    #include "pins_arduino.h"
    #include "WConstants.h"
#endif

#include <IRremote.h>

const uint32_t STATUS_MASK = 0xFFFF0000;
const uint32_t PLAYER_MASK = 0x0000FFFF;

enum
{
    COMMAND = 0x0,
    TEAM_A = 0x01,
    TEAM_B = 0x02,
    UPGRADE_RAPID = 0x0004,
    UPGRADE_INVULN = 0x0008,
    UPGRADE_INVIS = 0x0010,
    UPGRADE_SPY = 0x0020,
    UPGRADES = 0x0080
};




#endif
