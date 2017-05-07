
#include <LaserGun.h>

int PLAYER_NUMBER = 23;
int compin = 9;
int trigger = 5;
int fire = 3;
int laser = 4;
int sendpin = 6;

int trigger_moment = -1;
int ir_sensor_time = 30;


int score = 0;

IRrecv ir = IRrecv(9);
decode_results res;

bool sw = false;
int leds = 13;

LaserGun gun(PLAYER_NUMBER, compin, trigger, fire, laser, sendpin);

void setup()
{
    Serial.begin(9600);
    pinMode(leds, OUTPUT);
    digitalWrite(leds, HIGH);
}

void loop()
{
    if (gun.trigger())
    {
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
    if (ir.decode(&res))
    {
        unsigned int recv_val = res.value;
        Serial.println(recv_val);
        uint8_t t = (recv_val >> 24);
        uint8_t plnum = (recv_val & 0x00FF0000) >> 16;
        uint8_t num = (recv_val & 0x0000FF00) >> 8;
        uint8_t chk = (recv_val & 0x000000FF);
        
        if (checksum(recv_val) == chk)
        {
            if (t == COMMAND)
            {
                if (num == PLAYER_NUMBER)
                {
                    score++;
                    Serial.println(score);
                }
            }
        }
    }
}

void play_sound()
{

}