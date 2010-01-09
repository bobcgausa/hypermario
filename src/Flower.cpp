#include "Flower.h"

#include <cstdio>

Flower::Flower(Map* map) : Ennemy(map)
{
    _img.LoadFromFile("media/ennemys/flower.bmp");
    _img.CreateMaskFromColor(sf::Color(208, 214, 226));

    this->SetImage(_img);
    this->Resize(24.f, 48.f);

    _id = FLOWER;
}

Flower::~Flower()
{

}

void Flower::evolue(void)
{
    float time = _clock.GetElapsedTime() ;

    if (time >= 1)
    {
        _draw = _draw == false ? true : false;
        _clock.Reset() ;
    }

}
