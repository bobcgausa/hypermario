#ifndef ENNEMY_H
#define ENNEMY_H

#include "Mario.h"
/** Procéder par type ou par dérivation de classe ? **/

/* enum ENNEMY
{
    GOOMBA, FLOWER, KOOPA
}; */

class Ennemy : public sf::Sprite
{
    public:
        Ennemy(Map* );

        virtual ~Ennemy();

        virtual void evolue(void) = 0;

    protected:
        WHAT _status;
        sf::Clock _clock;
        sf::Image _img;
        Map* _map;
};

#endif // ENNEMY_H
