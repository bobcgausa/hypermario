#include "Mario.h"
#include <iostream>

Mario::Mario(Map* map) : sf::Sprite()
{
    m_map = map;

    m_img.LoadFromFile("media/mario.bmp");
    m_img.CreateMaskFromColor(sf::Color(208, 214, 226));

    SetImage(m_img);
    Resize(32.0f, 32.0f);
    SetY(384.0f);
    SetX(160.0f);
}

void Mario::jump(void)
{

}

void Mario::evolue(WHAT action)
{
    int caseX = this->GetPosition().x / 32;
    int caseY = this->GetPosition().y / 32;

    int vx = action == RIGHT ? 1 : -1;

    if (this->GetSubRect().Intersects(m_map->getTiles(caseX + action, caseY).spr.GetSubRect())
        && m_map->getTiles(caseX + action, caseY).type != SKY)
    {
        // collision, on ne se déplace pas   
    }

    else
    {
        this->Move(vx, 0);
    }
}



