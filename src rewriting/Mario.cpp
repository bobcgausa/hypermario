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
    {
        _vyJ = -3;
        _status = FALL;
    }

    else
        this->_vyJ += 0.1;
}

void Mario::fall(void)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    //if (this->GetSubRect().Intersects(_map->getTiles(caseX, caseY + 1).spr.GetSubRect()))
    if (_map->getTiles(caseX, caseY + 1).type == GROUND 
        || _map->getTiles(caseX, caseY + 1).type == BOX
        || _map->getTiles(caseX, caseY + 1).type == WALL)
    {
        _status = ON_THE_GROUND;
        _vyF = 0;
        return;
    }

    this->Move(0, _vyF);
    _vyF += 0.1;
}

WHAT& Mario::status()
{
    return _status;
}

void Mario::evolue(WHAT action)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    if (_status == JUMP)
    {
        this->jump();
    }

    else if (_status == FALL)
    {
        this->fall();
    }

    else if (action == RIGHT || action == LEFT)
    {
        int vx = action == RIGHT ? 1 : -1;

        /*if (this->GetSubRect().Intersects(_map->getTiles(caseX + action, caseY).spr.GetSubRect())
                && _map->getTiles(caseX + action, caseY).type != SKY)*/
        if (_map->getTiles(caseX + action, caseY).type != SKY)
        {
            // collision, on ne se déplace pas
        }

        else
        {
            this->Move(vx, 0);
        }
    }
}



