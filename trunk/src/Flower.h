#ifndef FLOWER_H
#define FLOWER_H

#include "Ennemy.h"

class Flower : public Ennemy
{
    public:
        Flower(Map* );
        virtual ~Flower();

        virtual void evolue(void);
    private:
};

#endif // FLOWER_H
