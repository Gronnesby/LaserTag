#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"


// Global constants
const long c_debounceTime = 10;
const int nbits = sizeof(unsigned long) * 8;

// Button debounce variables
struct buttonDebounce
{
    byte previousState;
    byte currentState;
    long lastTime;

    byte pressed;
    byte hold;
    volatile byte justPressed;
    volatile byte justReleased;
};
typedef struct buttonDebounce buttonDebounce_t;

// Laser gun variables & constants
struct laser_gun
{
    const int trigger;
    const int fire;
    const int laser;
    const int vest_com;

    const uint8_t player_num;
    uint8_t team;
    buttonDebounce_t bd;

    IRrecv recv;
    IRsend send;
    decode_results results;
};
typedef struct laser_gun laser_gun_t;

// Trigger function with button debouncing.
bool trigger(laser_gun_t& l);

// Fire function for sending an IR signal
bool fire(laser_gun_t& l);

// Communication with the vest to check if we can fire
bool canFire(laser_gun_t& l);

// Release the trigger
void triggerRelease(laser_gun_t& l);

// Create an 8-bit checksum based on a 32-bit message
unsigned long checksum(unsigned long msg);

#endif
