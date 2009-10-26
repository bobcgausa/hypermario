#include "Mario.h"
#include <iostream>

Mario::Mario(Map* map) : sf::Sprite()
{
    _map = map;

    _img.LoadFromFile("media/mario.bmp");
    _img.CreateMaskFromColor(sf::Color(208, 214, 226));

    SetImage(_img);
    Resize(32.0f, 32.0f);
    SetY(384.0f);
    SetX(160.0f);

    _vyJ = -3;
    _vyF = 0;
    _status = ON_THE_GROUND;
}

void Mario::jump(void)
{
    this->Move(0, _vyJ);

    // Si mario attend son point culminant de son saut, alors il tombe
    if (this->_vyJ >= 0)
        this->_status = FALL;
    else
        this->_vyJ += 0.1;
}

void Mario::fall(void)
{
    this->Move(0, _vyF);

    this->_vyF += 0.1;
}

const WHAT Mario::status() const
{
    return _status;
}

WHAT& Mario::status()
{
    return _status;
}

void Mario::evolue(WHAT action)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    if (action == JUMP || action == FALL)
    {
        int vy = action == JUMP ? 0 : 1;

        if (this->GetSubRect().Intersects(_map->getTiles(caseX, caseY + vy).spr.GetSubRect())
                && _map->getTiles(caseX, caseY + vy).type != SKY)
        {
            if (this->_status == JUMP)
            {
                this->_vyJ = -3;
                this->_status = FALL;
            }
            else if (this->_status == FALL)
            {
                this->_vyF = 0;
                this->_status = ON_THE_GROUND;
            }
        }
        else
        {
            if (action == JUMP)
                this->jump();
            else
                this->fall();
        }
    }
    else
    {
        int vx = action == RIGHT ? 1 : -1;

        if (this->GetSubRect().Intersects(_map->getTiles(caseX + action, caseY).spr.GetSubRect())
                && _map->getTiles(caseX + action, caseY).type != SKY)
        {
            // collision, on ne se déplace pas
        }

        else
        {
            this->Move(vx, 0);
        }
    }
}



