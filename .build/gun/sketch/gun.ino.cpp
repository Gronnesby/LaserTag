#include <Arduino.h>
#line 1 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
#line 1 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"

#include <LaserGun.h>

int playernum = 23;
int compin = 9;
int trigger = 5;
int fire = 3;
int laser = 4;
int sendpin = 6;

int interrupt = 2;
int trigger_moment = -1;
int ir_sensor_time = 50;

IRrecv ir();
unsigned long recv_val = -1;

bool sw = false;

int leds = 13;

LaserGun gun(playernum, compin, trigger, fire, laser, interrupt, sendpin);

#line 24 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void setup();
#line 33 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void loop();
#line 49 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void process_ir_input();
#line 63 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void play_sound();
#line 69 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void recv_ir_signal();
#line 24 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
void setup()
{
    Serial.begin(9600);
    pinMode(leds, OUTPUT);
    pinMode(interrupt, INPUT_PULLUP);

    digitalWrite(leds, HIGH);
}

void loop()
{
    if (gun.trigger())
    {
        sw = !sw;
        digitalWrite(sendpin, (sw) ? HIGH : LOW);
        trigger_moment = millis();
    }
    while ((trigger_moment != -1) && ((millis() - trigger_moment) < ir_sensor_time))
    {
        process_ir_input();
    }

    trigger_moment = -1;
}

void process_ir_input()
{
    if (recv_val != -1)
    {
        uint8_t t = (recv_val >> 24);
        uint8_t plnum = (recv_val & 0x00FF0000) >> 16;
        uint8_t chk = (recv_val & 0x000000FF);
        recv_val = -1;
    }
    else
    {
    }
}

void play_sound()
{

}


void recv_ir_signal()
{
    
}
