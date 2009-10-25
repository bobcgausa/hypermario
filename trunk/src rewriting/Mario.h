#ifndef MARIO_H
#define MARIO_H

#include <SFML/Graphics.hpp>

enum {JUMP, FALL, ON_THE_GROUND} ;

class Mario : public sf::Sprite
{
public:
    Mario();

private:
    sf::Image m_img;
};

#endif // MARIO_H
