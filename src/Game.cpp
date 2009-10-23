#include "Game.h"

#include <stdexcept>
#include <iostream>

Game::Game() : sf::RenderWindow(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "Mario")
{
    mario_ = NULL;
    try
    {
        mario_ = new Mario;
        createTiles();
    }
    catch (const std::runtime_error& e)
    {
        delete mario_;

        std::cerr << e.what() << std::endl;
        throw;
    }
}

Game::~Game()
{
    delete mario_;
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
    mario_->onDraw(*this);
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
    const sf::Vector2f marioPos = mario_->pos() ;

    if (GetEvent(E))
    {
        if (E.Type == sf::Event::Closed)
            Close();
    }

    if (I.IsKeyDown(sf::Key::Right))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, RIGHT))
        {
            mario_->x()++;
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Left))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, LEFT))
        {
            mario_->x()--;
            clock_.Reset();
        }
    }
    if (I.IsKeyDown(sf::Key::Up))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, UP))
        {
            mario_->jump();
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Down))
    {
        /*if (lastTime > 0.005 && !map_.detectCollision(marioPos, DOWN))
        {
            clock_.Reset();
            mario_->y()++;
        }*/
    }

    // Si Mario saute et que la case du dessus n'est pas le ciel
    if (mario_->status() == JUMP)
    {
        if (!map_.detectCollision(marioPos, UP))
            mario_->doJump();
        else
            mario_->isFalling();

    }
    else if (mario_->status() == FALL)
    {
        if (!map_.detectCollision(marioPos, DOWN)) mario_->doJump();
        else
            mario_->isOnTheGround();
    }

    if (I.IsMouseButtonDown(sf::Mouse::Right))
    {
        system("cls");
        std::cout << mario_->x() / 32 << " et " << mario_->y() / 32 << std::endl;
    }
}

/** Toute la fonction est à corriger (remplacer les casts et modifier les conditions) **/

bool Map::detectCollision(const sf::Vector2f& pos, int direction)
{
    sf::Vector2i marioCase;
    marioCase.x = static_cast<int>(pos.x / 32), marioCase.y = static_cast<int>(pos.y / 32);

    if (direction == UP || direction == DOWN)
    {
        if (map_[marioCase.x][marioCase.y + (direction == UP ? -1 : 1)] != SKY)
            return true;
        /*else if (map_[marioCase.x / 32)][marioCase.y / 32) + (direction == UP ? -1 : 1)] == SKY &&
                 map_[static_cast<int>((pos.x + 30) / 32)][marioCase.y / 32) + (direction == UP ? -1 : 1)] != SKY)
            return true;*/
    }
    else if (direction == RIGHT || direction == LEFT)
    {
        if (map_[marioCase.x + (direction == RIGHT ? 1 : 0)][marioCase.y] != SKY)
            return true;
        /*else if (map_[marioCase.x / 32) + (direction == RIGHT ? 1 : -1)][marioCase.y / 32)] == SKY &&
                 map_[marioCase.x / 32) + (direction == RIGHT ? 1 : -1)]
                 [marioCase.y / 32) + (direction == RIGHT ? 1 : -1)] != SKY)
            return true;*/
    }
    return false;
}

void Game::createTiles()
{
    sf::Image allTiles;
    try
    {
        if (!allTiles.LoadFromFile("media/tiles.bmp"))
            throw std::runtime_error("File can't be open");
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
        tiles_[i].CreateMaskFromColor(mask);
    }
}
