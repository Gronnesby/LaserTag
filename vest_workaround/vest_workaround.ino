/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <LaserTag.h>

int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;

int ledpin = 7;
int ledstate = HIGH;

uint16_t team = TEAM_B;
bool dead = false;

long tod = 0;
long death_time = 5000;
long led_timer = 0;

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(7, OUTPUT);
    digitalWrite(ledpin, ledstate);
}

void loop() {

    if(!dead)
    {
        decode_message();
    }
    else
    {
        if ((tod > 0) && ((millis() - tod) > death_time))
        {
            dead = false;
            tod = 0;
            ledstate = HIGH ;
            digitalWrite(ledpin, ledstate);
            irrecv.resume();
        }
        else
        {
            blink_led();
        }
    }

    delay(10);

  // vest.receive();
}

void decode_message()
{
    unsigned long val = 0;
    unsigned long plnum = 0;
    unsigned long t = 0;

    if (irrecv.decode(&results))
    {
        val = results.value;
        t = (val >> 16);
        plnum = (val & 0x0000FFFF);
        if(t != team)
        {
            Serial.println("Shot by:");
            Serial.println(plnum);
            dead = true;
            tod = millis();
            led_timer = millis();
            return;
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
            ledstate = LOW;
        }
        else
        {
            ledstate = HIGH;
        }

        digitalWrite(ledpin, ledstate);
    }
}
