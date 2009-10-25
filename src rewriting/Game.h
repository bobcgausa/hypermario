#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

enum {LEFT, RIGHT, UP, DOWN};

const sf::Color mask(208, 214, 226);

#include "Map.h"
#include "Mario.h"

class Game : public sf::RenderWindow
{
public:
    Game();

    virtual ~Game();

    void drawAll(void);

    void checkEvent(void);

    void evolue(void);

private:
    Map m_map;
    Mario m_mario;
};

#endif // GAME_H
