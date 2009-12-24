#include "Flower.h"

Flower::Flower(Map* map) : Ennemy(map)
{
    _img.LoadFromFile("media/ennemys/flower.bmp");
    _img.CreateMaskFromColor(sf::Color(208, 214, 226));

    this->SetImage(_img);
    this->Resize(24.f, 48.f);
}

Flower::~Flower()
{

}

void Flower::evolue(void)
{

}
