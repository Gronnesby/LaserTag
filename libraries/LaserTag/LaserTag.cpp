
#include "LaserTag.h"

unsigned long checksum(unsigned long msg)
{
    unsigned long team = (msg >> 24);
    unsigned long plnum = (msg & 0x00FF0000) >> 16;

    unsigned long chksum = (team + plnum) % 255;

    return chksum;
}