#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"

const int lockoutMillis = 6000;

class LaserVest
{
    public:
        // Constructor
        LaserVest(int playernum, int team, int compin, int sensorpin, IRrecv& ir, decode_results& res):
        m_playernum(playernum),
        m_compin(compin),
        m_sensorpin(sensorpin),
        m_team(team),
        m_irrecv(ir),
        m_res(res)
        {
            pinMode(m_compin, OUTPUT);
            digitalWrite(m_compin, HIGH);
            
            m_irrecv.enableIRIn();
            alive = true;
            m_ledState = HIGH;
            m_tod = 0;
            m_ledTimer = 0;
            m_score = 0;
            m_res = decode_results{};

            // m_strip = Adafruit_NeoPixel(20, 12, NEO_GRB + NEO_KHZ800);

            // m_strip.begin();
            // if (m_team == TEAM_A)
            // {
            //     for(int i = 0; i < 20; i++)
            //     {
            //         m_strip.setPixelColor(i, 0, 255, 0);
            //     }
            // }
            // else
            // {
            //     for(int i = 0; i < 20; i++)
            //     {
            //         m_strip.setPixelColor(i, 0, 0, 255);
            //     }
            // }
            
            // m_strip.setBrightness(15);
            // m_strip.show();
        }

        // Receives a message over the registered sensorpin
        void receive();

        void lockout();

        // Decode the message received via IR
        void decodeMessage(unsigned long val);

        // Enables weapon, does nothing if the weapon is enabled
        void enableWeapon();

        bool alive;

    private:

        // Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
        void disableWeapon();



        

        void blinkLeds();

        unsigned int m_playernum;
        int m_compin;
        int m_sensorpin;

        long m_tod;
        long m_ledTimer;
        int m_ledState;

        uint16_t m_team;
        uint32_t m_teamColor;
        unsigned int m_score;

        Adafruit_NeoPixel m_strip;

        decode_results m_res;
        IRrecv m_irrecv;
};

#endif
