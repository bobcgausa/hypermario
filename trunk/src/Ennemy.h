#ifndef ENNEMY_H
#define ENNEMY_H

#include <SFML\Graphics.hpp>

enum ENNEMY
{
    GOOMBA, FLOWER, KOOPA
};

class Ennemy : public sf::Sprite
{
    public:
        Ennemy();

        ~Ennemy();

    private:
};

#endif // ENNEMY_H
