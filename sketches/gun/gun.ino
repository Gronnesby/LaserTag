
#include <LaserGun.h>

IRrecv recv = IRrecv(2);
IRsend send = IRsend();

laser_gun_t gun = laser_gun_t
{
    5,      // Trigger
    3,      // Fire
    4,      // Laser
    10,     // Vest com
    
    9,                 // Player Number
    TEAM_A,             // Team
    buttonDebounce_t{}, // Debounce struct

    recv,               // IR receiver
    send,               // IR sender
    decode_results{}    // IR results
};


int trigger_moment = -1;
int ir_sensor_time = 70;
int leds = 13;
int score = 0;
int speaker = A0;

void setup()
{
    Serial.begin(9600);
    pinMode(leds, OUTPUT);
    pinMode(gun.trigger, INPUT);
    pinMode(gun.vest_com, INPUT);
    pinMode(gun.laser, OUTPUT);

    gun.recv.enableIRIn();

    digitalWrite(leds, HIGH);
}

void loop()
{
    if (trigger(gun))
    {
        play_sound();
        trigger_moment = millis();
    }
    // while ((trigger_moment != -1) && ((millis() - trigger_moment) < ir_sensor_time))
    // {
    //     process_ir_input();
    // }

    trigger_moment = -1;
}

void process_ir_input()
{
    if (gun.recv.decode(&gun.results))
    {
        unsigned int recv_val = gun.results.value;
        Serial.println(recv_val);
        uint8_t t = (recv_val >> 24);
        uint8_t plnum = (recv_val & 0x00FF0000) >> 16;
        uint8_t num = (recv_val & 0x0000FF00) >> 8;
        uint8_t chk = (recv_val & 0x000000FF);
        
        if (checksum(recv_val) == chk)
        {
            if (t == COMMAND)
            {
                if (num == gun.player_num)
                {
                    score++;
                    Serial.println(score);
                }
            }
        }
    }
    gun.recv.resume();
}

void play_sound()
{
        for (int i = 5000; i > 800; i--)
        {
            analogWrite(speaker, (i*50));
        }
}