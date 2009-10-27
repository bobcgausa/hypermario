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

    _vyJ = -4;
    _vyF = 0;
    _status = ON_THE_GROUND;
}

void Mario::jump(void)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    // Si mario attend son point culminant de son saut, ou si on détecte une collision, alors il tombe
    if (_vyJ >= 0 || _map->getTiles(caseX, caseY).type != SKY)
    {
        _status = FALL;
        _vyJ = -4;

        return;
    }

    this->Move(0, _vyJ);
    _vyJ += 0.1;
}

void Mario::fall(void)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);

    //if (this->GetSubRect().Intersects(_map->getTiles(caseX, caseY + 1).spr.GetSubRect()))
    if (_map->getTiles(caseX, caseY + 1).type != SKY)
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
    if (action == RIGHT || action == LEFT)
    {
        int caseX = static_cast<int>(this->GetPosition().x / 32);
        int caseY = static_cast<int>(this->GetPosition().y / 32);

        int vx = action == RIGHT ? 1 : -1;

        /*if (this->GetSubRect().Intersects(_map->getTiles(caseX + action, caseY).spr.GetSubRect())
                && _map->getTiles(caseX + action, caseY).type != SKY)*/
        if (_map->getTiles(caseX + action, caseY).type != SKY)
            // collision, on ne se déplace pas
        {
        }

        else
        {
            this->Move(vx, 0);
        }

        if (_status == ON_THE_GROUND && _map->getTiles(caseX, caseY + 1).type == SKY)
            _status = FALL;
    }

    if (action == JUMP)
    {
        this->jump();
    }

    if (action == FALL)
    {
        this->fall();
    }


}



