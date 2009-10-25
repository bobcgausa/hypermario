#ifndef MARIO_H
#define MARIO_H

#include <SFML/Graphics.hpp>
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

private:
    void jump(void);

    Map* m_map;
    sf::Image m_img;
};

#endif // MARIO_H
