#ifndef __LASER_GUN_H__
#define __LASER_GUN_H__

#include "LaserTag.h"


// Global constants
const long c_debounceTime = 10;
const int nbits = sizeof(unsigned long) * 8;

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

struct laser_gun
{
    int trigger;
    int fire;
    int laser;
    int vest_com;

    uint8_t player_num;
    uint8_t team;
    buttonDebounce_t bd;

    IRrecv recv;
    IRsend send;
    decode_results results;
};
typedef struct laser_gun laser_gun_t;

/// Trigger function with button debouncing.
/**
 *
 * 
 */
//bool trigger(laser_gun_t& l);

// Fire function for sending an IR signal
//bool fire(laser_gun_t& l);

// Communication with the vest to check if we can fire
//bool canFire(laser_gun_t& l);

// Release the trigger
//void triggerRelease(laser_gun_t& l);

// Create an 8-bit checksum based on a 32-bit message
unsigned long checksum(unsigned long msg);

class LaserGun
{
    public:
        LaserGun(int playernum, int compin, int triggerpin, int firepin, int laserpin, int irpin) :
        m_playernum(playernum),
        m_triggerpin(triggerpin),
        m_firepin(firepin),
        m_compin(compin),
        m_laserpin(laserpin),
        m_irsend(IRsend()),
        irrecv(IRrecv(irpin))
        {
            m_team = TEAM_A;

            m_debounce = buttonDebounce_t{};
            results = decode_results{};
            
            pinMode(m_triggerpin, INPUT);
            pinMode(m_compin, INPUT);
            pinMode(m_laserpin, OUTPUT);

        }

        // Trigger function with button debouncing
        bool trigger();

        // Receive from the gun IR sensor
        // Used for upgrades, commands and point-counting
        void recvIRSignal();

        // Received value from the IR sensor
        volatile int recvVal;

        decode_results results;
        IRrecv irrecv;

    private:

        // Fire function for sending an IR signal
        bool fire();

        // Communication with the vest to check if we can fire
        bool canFire();

        // Release the trigger
        void triggerRelease();

        // Play gun sound
        void playSound(int sound);

        int m_triggerpin;
        int m_firepin;
        int m_compin;
        int m_laserpin;

        buttonDebounce_t m_debounce;

        uint8_t m_playernum;
        uint8_t m_team;
        uint16_t m_upgrades;
        IRsend m_irsend;
};



#endif
