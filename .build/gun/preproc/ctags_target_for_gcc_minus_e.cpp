# 1 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"
# 1 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino"

# 3 "/Users/gronnesby/Documents/arduino/sketches/gun/gun.ino" 2

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

void setup()
{
    Serial.begin(9600);
    pinMode(leds, 0x1);
    pinMode(interrupt, 0x2);

    digitalWrite(leds, 0x1);
}

void loop()
{
    if (gun.trigger())
    {
        sw = !sw;
        digitalWrite(sendpin, (sw) ? 0x1 : 0x0);
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
