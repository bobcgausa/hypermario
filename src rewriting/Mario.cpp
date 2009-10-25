#include "Mario.h"

Mario::Mario() : sf::Sprite()
{
    m_img.LoadFromFile("media/mario.bmp");
    m_img.CreateMaskFromColor(sf::Color(208, 214, 226));

    SetImage(m_img);
    Resize(32.0f, 32.0f);
    SetY(384.0f);
    SetX(160.0f);
}





