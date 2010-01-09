#include "Goomba.h"

Goomba::Goomba(Map* map) : Ennemy(map)
{
    _img.LoadFromFile("media/ennemys/goomba.bmp");
    _img.CreateMaskFromColor(sf::Color(208, 214, 226));

    this->SetImage(_img);
    this->Resize(24.0f, 24.0f);

    _direction = LEFT;

    _id = GOOMBA;
}

Goomba::~Goomba()
{
}

bool Goomba::detectCollision(WHAT direction)
{
    int caseX = static_cast<int>((this->GetPosition().x + (direction == RIGHT ? 24 : -1)) / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    if (this->GetPosition().x > 0 && _map->getTiles(caseX, caseY).type == SKY)
        return false;

    return true;
}

void Goomba::evolue(void)
{
    float time = _clock.GetElapsedTime() ;
    if (time >= 0.005)
    {
        int vx = _direction == RIGHT ? 2 : -2;

        if (!this->detectCollision(_direction))
        {
            this->Move(vx, 0);
            _clock.Reset();
        }
        else
        {
            _direction = (_direction == LEFT ? RIGHT : LEFT);
        }
    }
}
