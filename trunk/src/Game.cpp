#include "Game.h"

#include <stdexcept>
#include <iostream>

Game::Game() : sf::RenderWindow(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDHT), "Mario"), mario_()
{
    try
    {
        createTiles();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }
}

Game::~Game()
{
}

void Game::loadMap(const sf::Image& map)
{
    map_.createFrom(map);
}

void Game::drawMap()
{
    map_.onDraw(*this, tiles_) ;
}

void Game::drawMario()
{
    mario_.onDraw(*this);
}

void Game::drawAll()
{
    drawMap();
    drawMario();
}

void Game::onEvent()
{
    sf::Event E;
    const sf::Input& I = GetInput();

    lastTime = clock_.GetElapsedTime();
    const sf::Vector2f marioPos = mario_.pos() ;

    if (GetEvent(E))
    {
        if (E.Type == sf::Event::Closed)
            Close();
    }

    if (I.IsKeyDown(sf::Key::Right))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, RIGHT))
        {
            mario_.x()++;
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Left))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, LEFT))
        {
            mario_.x()--;
            clock_.Reset();
        }
    }
    if (I.IsKeyDown(sf::Key::Up))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, UP))
        {
            mario_.jump();
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Down))
    {
        /*if (lastTime > 0.005 && !map_.detectCollision(marioPos, DOWN))
        {
            clock_.Reset();
            mario_.y()++;
        }*/
    }

    // Si Mario saute et que la case du dessus n'est pas le ciel
    if (mario_.status() == JUMP)
    {
        if (!map_.detectCollision(marioPos, UP))
            mario_.doJump();
        else
            mario_.isFalling(), puts("PASSADE");

    }
    else if (mario_.status() == FALL)
    {
        if (!map_.detectCollision(marioPos, DOWN)) mario_.doJump();
        else
            mario_.isOnTheGround();
    }

    if (I.IsMouseButtonDown(sf::Mouse::Right))
    {
        system("cls");
        std::cout << mario_.x() / 32 << " et " << mario_.y() / 32 << std::endl;
    }
}

/** Toute la fonction est à corriger (remplacer les casts et modifier les conditions) **/

bool Map::detectCollision(const sf::Vector2f& pos, int direction)
{
    if (direction == UP || direction == DOWN)
    {
        if (static_cast<int>(pos.y) % 32 == 0)
        {
            if (map_[static_cast<int>(pos.x / 32)][static_cast<int>(pos.y / 32) + (direction == UP ? -1 : 1)] != SKY)
                return true;
            /*else if (map_[static_cast<int>(pos.x / 32)][static_cast<int>(pos.y / 32) + (direction == UP ? -1 : 1)] == SKY &&
                     map_[static_cast<int>((pos.x + 30) / 32)][static_cast<int>(pos.y / 32) + (direction == UP ? -1 : 1)] != SKY)
                return true;*/
        }
    }
    else if (direction == RIGHT || direction == LEFT)
    {
        if (static_cast<int>(pos.x) % 32 == 0)
        {
            if (map_[static_cast<int>(pos.x / 32) + (direction == RIGHT ? 1 : -1)][static_cast<int>(pos.y / 32)] != SKY)
                return true;
            /*else if (map_[static_cast<int>(pos.x / 32) + (direction == RIGHT ? 1 : -1)][static_cast<int>(pos.y / 32)] == SKY &&
                     map_[static_cast<int>(pos.x / 32) + (direction == RIGHT ? 1 : -1)]
                     [static_cast<int>(pos.y / 32) + (direction == RIGHT ? 1 : -1)] != SKY)
                return true;*/
        }
    }
    return false;
}

void Game::createTiles()
{
    sf::Image allTiles;
    try
    {
        if (!allTiles.LoadFromFile("media/tile2s.bmp"))
            throw std::runtime_error("Can't open media/tiles.bmp");
    }
    catch (const std::exception& e)
    {
        throw;
    }

    tiles_.resize(7);

    for (Uint i = 0; i < tiles_.size(); i++)
    {
        tiles_[i].Create(32, 32);
        tiles_[i].Copy(allTiles, 0, 0, sf::IntRect(i * 32, 0, (i + 1) * 32, 32));
        tiles_[i].CreateMaskFromColor(sf::Color(208, 214, 226));
    }
}
