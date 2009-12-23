#ifndef MARIO_H
#define MARIO_H

#include "Map.h"

enum WHAT
{
    LEFT, RIGHT, JUMP, FALL, ON_THE_GROUND
};

class Mario : public sf::Sprite
{
public:
    Mario(Map*);

    void evolue(WHAT action = ON_THE_GROUND);

    WHAT& status() ;

private:
    void jump(void);
    void fall(void);

    Map* _map;
    sf::Image _img;

    double _vyJ;
    double _vyF;
    WHAT _status;
};

#endif // MARIO_H
