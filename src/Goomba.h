#ifndef GOOMBA_H
#define GOOMBA_H

#include "Ennemy.h"

class Goomba : public Ennemy
{
    public:
        Goomba(Map* ) ;

        virtual ~Goomba() ;

        virtual void evolue(void) ;
        bool detectCollision(WHAT ) ;

    private:
        WHAT _direction;

} ;

#endif // GOOMBA_H
