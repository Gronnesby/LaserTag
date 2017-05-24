#ifndef __LASER_VEST_H__
#define __LASER_VEST_H__

#include "LaserTag.h"
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <IRremote.h>

const int lockoutMillis = 6000;

// Laser gun variables & constants
struct laser_vest
{
    const int to_gun;           // Compin to the gun
    const int from_gun;         // Compin from the gun
    const int white_leds;       // White led pin, white leds on the sensor plates
    int ledstate;               // State of the white leds (and the pixel strip)

    const uint8_t player_num;   // Unique player id
    uint8_t team;               // Team of the player
    uint32_t teamcolor;         // Color of the team (neopixel strip colors)

    bool alive;                 // Is the player alive or not
    long tod;                   // The time the player got shot in ms, 0 if alive
    long shot_by;               // Who did i get shot by?
    long lockout_time;          // The time the player is locked out after getting shot
    long game_time;             // How long the current game lasts
    long blink_timer;           // Should the leds flip color (if the player got shot)
    int score;

    const int pixel_pin;        // Datapin connected to the neopixel strip
    const int npixels;          // Number of pixels, default: 17
    Adafruit_NeoPixel strip;    // Neopixel strip object

    //SoftwareSerial ser;         // Software serial object to communicate with mp3 player
    //uint8_t sendbuf[8];         // Send buffer for the software serial

    IRrecv recv;                // IR receive object
    IRsend send;                // IR send object
    decode_results results;     // Result struct for the IR receiver
};
typedef struct laser_vest laser_vest_t;


// Decode the message received via IR
void decodeMessage(unsigned long val);

// Enables weapon, does nothing if the weapon is enabled
void enableWeapon(laser_vest_t &v);

// Blinks an IR signal from the sensor plates of the vest
void sendSignal(laser_vest_t &v);

// Disables the weapon by communicating over the compin, does nothing if weapon is aleady disabled
void disableWeapon(laser_vest_t &v);

// Blinks all leds on the vest
void blinkLeds(laser_vest_t &v);

// Sets the color of the neopixel strip
void setStripColor(laser_vest_t &v, uint32_t col);

#endif
