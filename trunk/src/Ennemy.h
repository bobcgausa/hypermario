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
        Ennemy();

        virtual ~Ennemy();

        virtual void evolue(void) = 0;

    protected:
        WHAT _status;
        sf::Image _img;
};

class Goomba : public Ennemy
{
    public:
        Goomba(Map* ) ;

        virtual ~Goomba() ;

        virtual void evolue(void) ;
        bool detectCollision(WHAT ) ;

    private:
        WHAT _direction;
        sf::Clock _clock;
        Map* _map;

} ;

#endif // ENNEMY_H
