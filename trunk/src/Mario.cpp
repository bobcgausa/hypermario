#include "Mario.h"

#include <SFML/Graphics.hpp>

#include <iostream>

Mario::Mario()
{
    img_ = new sf::Image;
    img_->LoadFromFile("mario.bmp");
    img_->CreateMaskFromColor(sf::Color(208, 214, 226));

    pos_.x = 160;
    pos_.y = 384;

    status_ = ON_THE_GROUND;
    v_y = -4;
}

Mario::~Mario()
{
    delete img_;
}

void Mario::operator++()
{
    pos_.x++;
}

void Mario::operator--()
{
    pos_.x--;
}

float& Mario::x()
{
    return pos_.x;
}

float& Mario::y()
{
    return pos_.y;
}

void Mario::doJump()
{
    if (c_.GetElapsedTime() > 0.005)
    {
        pos_.y += v_y;
        if (v_y >= 0)
            status_ = FALL;

        v_y += 0.1;

        c_.Reset();
    }
}

int Mario::status() const
{
    return status_;
}

void Mario::jump()
{
    status_ = JUMP;
}

void Mario::isOnTheGround()
{
    v_y = -4;
    status_ = ON_THE_GROUND;
}

void Mario::isFalling()
{
    status_ = FALL;
    v_y = 0;
}

void Mario::onDraw(sf::RenderWindow& App)
{
    sf::Sprite* s = new sf::Sprite;

    s->SetImage(*img_);
    s->SetPosition(pos_);
    s->Resize(32, 32);

    App.Draw(*s);

    delete s;
}

sf::Vector2f Mario::pos() const
{
    return pos_;
}


