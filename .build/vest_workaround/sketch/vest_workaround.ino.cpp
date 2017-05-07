#include <Arduino.h>
#line 1 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
#line 1 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"


#include <IRremote.h>
#include <LaserTag.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define CMD_PLAY_W_INDEX 0x03

int SERIAL_RX = 5;
int SERIAL_TX = 6;
int PLAYER_NUMBER = 23;

int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
IRsend irsend();
decode_results results;

int toGunPin = 10;
int fromGunPin = 11;
int gunsound = HIGH;
int ledpin = 13;
int ledstate = HIGH;

uint16_t team = TEAM_B;
uint32_t teamcolor;
bool alive = true;
int flashback = 0;

long tod = 0;
long death_time = 6000;
long led_timer = 0;

int npixels = 17;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(npixels, 12, NEO_RGB + NEO_KHZ800);
SoftwareSerial ser(SERIAL_RX, SERIAL_TX);
int8_t sendbuf[8] = {0};

#line 39 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void setup();
#line 68 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void loop();
#line 101 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void decode_message();
#line 134 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void send_signal(unsigned long plnum);
#line 146 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void blink_led();
#line 174 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void play_sound(uint16_t num);
#line 39 "/Users/gronnesby/Documents/arduino/sketches/vest_workaround/vest_workaround.ino"
void setup()
{
    ser.begin(9600);
    irrecv.enableIRIn(); // Start the receiver

    pinMode(ledpin, OUTPUT);
    pinMode(toGunPin, OUTPUT);
    pinMode(fromGunPin, INPUT);
    digitalWrite(ledpin, ledstate);
    digitalWrite(toGunPin, HIGH);

    strip.begin();

    if (team == TEAM_B)
    {
        teamcolor = strip.Color(0, 255, 0);
    }
    else
    {
        teamcolor = strip.Color(0, 0, 255);
    }
        
    for(int i = 0; i < npixels; i++)
    {
        strip.setPixelColor(i, teamcolor);
    }
    strip.show();
}

void loop() {

    if(alive)
    {
        digitalWrite(toGunPin, HIGH);
        decode_message();
    }
    else
    {
        digitalWrite(toGunPin, LOW);
        if ((tod > 0) && ((millis() - tod) > death_time))
        {
            alive = true;
            tod = 0;
            ledstate = HIGH;
            digitalWrite(ledpin, ledstate);
            for(int i = 0; i < npixels; i++)
            {
                strip.setPixelColor(i, teamcolor);
            }
            strip.show();
            irrecv.resume();
        }
        else
        {
            blink_led();
        }
    }

    delay(10);

}

void decode_message()
{
    unsigned long val = 0;
    unsigned long plnum = 0;
    unsigned long t = 0;
    unsigned long chk = 0;

    if (irrecv.decode(&results))
    {
        val = results.value;
        t = (val >> 24);
        plnum = (val & 0x00FF0000) >> 16;
        chk = (val & 0x000000FF);

        if(chk != ((t + plnum) % 255))
        {
        }
        else
        {
            if(t != team && t != COMMAND)
            {
                alive = false;
                tod = millis();
                led_timer = millis();
                send_signal(plnum);
                return;
            }

        }
        irrecv.resume(); // Receive the next value
    }
}

void send_signal(unsigned long plnum)
{
    unsigned long flash_msg = 0;

    flash_msg = (((unsigned long) COMMAND) << 24) | (((unsigned long) plnum) << 16 | (((unsigned long) PLAYER_NUMBER) << 8);

    for (int i = 0; i < 3; i++)
    {
        irsend.sendSony(flash_msg, 32);
    }
}

void blink_led()
{
    if((millis() - led_timer) >= 300)
    {
        led_timer = millis();
        if (ledstate == HIGH)
        {
            for(int i = 0; i < npixels; i++)
            {
                strip.setPixelColor(i, 255, 0, 0);
            }
            ledstate = LOW;
            digitalWrite(ledpin, ledstate);
        }
        else
        {
            for(int i = 0; i < npixels; i++)
            {
                strip.setPixelColor(i, teamcolor);
            }
            ledstate = HIGH;
            digitalWrite(ledpin, ledstate);
        }
        strip.show();
    }
}


void play_sound(uint16_t num)
{

        sendbuf[0] = 0x7e; //starting byte
        sendbuf[1] = 0xff; //version
        sendbuf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
        sendbuf[3] = CMD_PLAY_W_INDEX; //
        sendbuf[4] = 0x00; //0x00 = no feedback, 0x01 = feedback
        sendbuf[5] = (int8_t)(num >> 8);//datah
        sendbuf[6] = (int8_t)(num); //datal
        sendbuf[7] = 0xef; //ending byte
        for(uint8_t i=0; i<8; i++)
        {
            ser.write(sendbuf[i]);
        }
        if (num == 1)
        {
            gunsound = !gunsound;
        }
}