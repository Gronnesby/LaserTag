

#include <IRremote.h>
#include <LaserTag.h>
#include <Adafruit_NeoPixel.h>

int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;

int toGunPin = 10;
int ledpin = 13;
int ledstate = HIGH;

uint16_t team = TEAM_B;
bool dead = false;

long tod = 0;
long death_time = 6000;
long led_timer = 0;

int npixels = 20;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(npixels, 12, NEO_RGB + NEO_KHZ800);

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver

    pinMode(ledpin, OUTPUT);
    pinMode(toGunPin, OUTPUT);
    digitalWrite(ledpin, ledstate);
    digitalWrite(toGunPin, HIGH);

    strip.begin();
    for(int i = 0; i < npixels; i++)
    {
        if (team == TEAM_B)
        {
            strip.setPixelColor(i, 0, 255, 0);
        }
        else
        {
            strip.setPixelColor(i, 0, 0, 255);
        }
        
    }
    strip.show();

}

void loop() {

    if(!dead)
    {
        digitalWrite(toGunPin, HIGH);
        decode_message();
    }
    else
    {
        digitalWrite(toGunPin, LOW);
        if ((tod > 0) && ((millis() - tod) > death_time))
        {
            dead = false;
            tod = 0;
            ledstate = HIGH ;
            digitalWrite(ledpin, ledstate);
            for(int i = 0; i < npixels; i++)
            {
                if (team == TEAM_B)
                {
                    strip.setPixelColor(i, 0, 255, 0);
                }
                else
                {
                    strip.setPixelColor(i, 0, 0, 255);
                }
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
          Serial.println("Corrupted value");  
        }
        else
        {
          if(t != team && t != COMMAND)
          {
              Serial.println("Shot by:");
              Serial.println(plnum);
              dead = true;
              tod = millis();
              led_timer = millis();
              return;
          }
          else if (t == COMMAND)
          {

          }
          else if (t == team)
          {
              
          }
        }
        irrecv.resume(); // Receive the next value
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
            //digitalWrite(ledpin, ledstate);
        }
        else
        {
            for(int i = 0; i < npixels; i++)
            {
                if (team == TEAM_B)
                {
                    strip.setPixelColor(i, 0, 255, 0);
                }
                else
                {
                    strip.setPixelColor(i, 0, 0, 255);
                }
            }
            ledstate = HIGH;
            //digitalWrite(ledpin, ledstate);
        }
        strip.show();
    }
}
