
#include <LaserVest.h>

#define CMD_PLAY_W_INDEX 0x03

Adafruit_NeoPixel strip = Adafruit_NeoPixel(17, 12, NEO_RGB + NEO_KHZ800);
SoftwareSerial ser(5, 6);
IRrecv irrecv = IRrecv(9);
IRsend irsend = IRsend();
decode_results results;

laser_vest_t vest
{
    10,     // To gun pin
    11,     // From gun pin
    13,     // White led pin (white leds on the sensor plates)
    HIGH,   // Ledstate

    3,      // Player num
    TEAM_B, // Team
    0x0,    // Teamcolor

    true,   // Alive or not
    0,      // Time of death
    0,      // Shot by
    6000,   // Lockout time
    300000, // Game time
    0,      // Blink timer
    0,      // Score

    12,     // Pixel data pin
    17,     // Num pixels
    strip,  // Pixel strip object

    irrecv, // Ir receive object
    irsend, // Ir send object
    decode_results{}    // Ir results
};


void setup()
{
    vest.recv.enableIRIn();


    pinMode(vest.white_leds, OUTPUT);
    pinMode(vest.to_gun, OUTPUT);
    pinMode(vest.from_gun, INPUT);
    digitalWrite(vest.white_leds, vest.ledstate);
    digitalWrite(vest.to_gun, HIGH);

    vest.strip.begin();
    vest.teamcolor = (vest.team == TEAM_A) ? vest.strip.Color(0, 0, 255) : vest.strip.Color(0, 255, 0);
    
    for(int i = 0; i < vest.npixels; i++)
    {
        vest.strip.setPixelColor(i, vest.teamcolor);
    }
    vest.strip.show();
}

void loop() {

    
    if(vest.alive)
    {
        enableWeapon(vest);
        vest.shot_by = decode_message();
    }
    else
    {
        disableWeapon(vest);
        while ((vest.tod > 0) && ((millis() - vest.tod) < vest.lockout_time))
        {
            blinkLeds(vest);
            sendSignal(vest);
        }
        vest.alive = true;
        vest.tod = 0;
        vest.ledstate = HIGH;
        vest.shot_by = 0;
        digitalWrite(vest.white_leds, vest.ledstate);
        setStripColor(vest, vest.teamcolor);
        vest.recv.enableIRIn();
        vest.recv.resume();
    }

}

unsigned long decode_message()
{
    unsigned long val = 0;
    unsigned long to = 0;
    unsigned long from = 0;
    unsigned long t = 0;
    unsigned long chk = 0;

    if (vest.recv.decode(&vest.results))
    {
        
        val = results.value;
        t = (val >> 24);
        from = (val & 0x00FF0000) >> 16;
        to = (val & 0x0000FF00) >> 8;
        chk = (val & 0x000000FF);

        if(chk == checksum(val))
        {
            if(t != vest.team && t != COMMAND)
            {
                vest.alive = false;
                vest.tod = millis();
                vest.blink_timer = millis();
                return from;
            }
            if (t == COMMAND)
            {

                if (to == vest.player_num && from != vest.player_num)
                {
                    vest.score++;
                }
            }
        }
        vest.recv.enableIRIn();
        vest.recv.resume();
    }
}


// Playing mp3 sounds is currently not implemented
// void play_sound(uint16_t num)
// {

//         vest.sendbuf[0] = 0x7e;                  // Starting byte
//         vest.sendbuf[1] = 0xff;                  // Version
//         vest.sendbuf[2] = 0x06;                  // The number of bytes of the command without starting byte and ending byte
//         vest.sendbuf[3] = CMD_PLAY_W_INDEX;      // Command
//         vest.sendbuf[4] = 0x00;                  // 0x00 = no feedback, 0x01 = feedback
//         vest.sendbuf[5] = (int8_t)(num >> 8);    // datah
//         vest.sendbuf[6] = (int8_t)(num);         // datal
//         vest.sendbuf[7] = 0xef;                  // Ending byte
        
//         for(uint8_t i=0; i<8; i++)
//         {
//             vest.ser.write(sendbuf[i]);
//         }
// }

