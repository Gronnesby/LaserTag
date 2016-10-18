#ifndef __LASER_TAG_H__
#define __LASER_TAG_H__


class LaserTag
{
    public:
        LaserTag(unsigned char player_number, bool vest);
        unsigned char ReadSignal();

    private:
        bool _vest;
        unsigned char _player_number;
}



#endif
