
#include <LaserGun.h>

int playernum = 23;
int compin = 9;
int trigger = 5;
int fire = 3;
int laser = 4;

int interrupt = 2;
int trigger_moment = -1;
int ir_sensor_time = 50;
unsigned long recv_val = 0;

int sw = LOW;

int leds = 13;

LaserGun gun(playernum, compin, trigger, fire, laser, interrupt);

void setup()
{
    Serial.begin(9600);
    pinMode(leds, OUTPUT);
    pinMode(interrupt, INPUT_PULLUP);

    digitalWrite(leds, HIGH);
    //attachInterrupt(digitalPinToInterrupt(interrupt), gun.recvIRSignal, CHANGE);
}

void loop()
{
    if (gun.trigger())
    {
        digitalWrite(compin, !sw);
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
        Serial.println(recv_val, HEX);
        recv_val = -1;
    }
    else
    {
        Serial.println("Corrupted Value");
    }
}

void play_sound()
{

}


void recv_ir_signal()
{
    
}