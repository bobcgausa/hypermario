#include "Mario.h"
#include <iostream>

using std::cout;
using std::endl;

Mario::Mario(Map* map) : sf::Sprite()
{
    _map = map;

    _img.LoadFromFile("media/mario.bmp");
    _img.CreateMaskFromColor(sf::Color(208, 214, 226));

    SetImage(_img);
    Resize(24.0f, 24.0f);
    SetY(488.0f);
    SetX(22.0f);

    _vyJ = -4;
    _vyF = 0.1;
    _status = ON_THE_GROUND;
}

void Mario::jump(void)
{
    int caseX = static_cast<int>(this->GetPosition().x / 32);
    int caseY = static_cast<int>(this->GetPosition().y / 32);
    int caseX2 = static_cast<int>((this->GetPosition().x + 23) / 32);

    // Si mario attend son point culminant de son saut, ou si on détecte une collision, alors il tombe
    if (_vyJ >= 0
        || _map->getTiles(caseX, caseY).type != SKY
        || _map->getTiles(caseX2, caseY).type != SKY)
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
    int caseX2 = static_cast<int>((this->GetPosition().x + 24) / 32);
    int caseY = static_cast<int>((this->GetPosition().y + 24 + _vyF) / 32);

    puts("JE PASSE !");

    if (_map->getTiles(caseX, caseY).type != SKY
        || _map->getTiles(caseX2, caseY).type != SKY)
    {
        cout << caseX2 << " et " << caseY << " et " << _map->getTiles(caseX2, caseY).type << endl;
        cout << this->GetPosition().x << " et " << this->GetPosition().x + 23 << endl;
        int y = static_cast<int>(this->GetPosition().y);

        while ((y + 24) % 32 != 0)
            ++y;
        this->SetY(y);

        _status = ON_THE_GROUND;
        _vyF = 0;

        return;
    }

    this->Move(0, _vyF);

    if (_vyF < 5)
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
        int vx = action == RIGHT ? 2 : -2;

        int caseX = static_cast<int>((this->GetPosition().x + (action == RIGHT ? 25 : -1)) / 32);
        int caseY = static_cast<int>(this->GetPosition().y / 32);
        int caseY2 = static_cast<int>((this->GetPosition().y + 22) / 32);

        if (_map->getTiles(caseX, caseY).type != SKY
            || _map->getTiles(caseX, caseY2).type != SKY)
        {
        }
        else
        {
            this->Move(vx, 0);
        }

        caseX = static_cast<int>(this->GetPosition().x / 32);

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



