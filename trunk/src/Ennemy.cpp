#include "Ennemy.h"
#include <iostream>

Ennemy::Ennemy(Map* map) : sf::Sprite()
{
    _map = map;
    _status = ON_THE_GROUND;

}

Ennemy::~Ennemy()
{

}


