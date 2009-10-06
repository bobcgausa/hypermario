#include "Game.h"

using namespace std;

#include <cmath>

Game::Game() : sf::RenderWindow(sf::VideoMode(640, 480), "Mario")
{
    createTiles(tiles_);
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
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, DROITE))
        {
            mario_.x()++;
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Left))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, GAUCHE))
        {
            mario_.x()--;
            clock_.Reset();
        }
    }
    if (I.IsKeyDown(sf::Key::Up))
    {
        if (lastTime > 0.005 && !map_.detectCollision(marioPos, HAUT))
        {
            mario_.jump();
            clock_.Reset();
        }
    }
    else if (I.IsKeyDown(sf::Key::Down))
    {
        /*if (lastTime > 0.005 && !map_.detectCollision(marioPos, BAS))
        {
            clock_.Reset();
            mario_.y()++;
        }*/
    }

    // Si Mario saute et que la case du dessus n'est pas le ciel
    if (mario_.status() == JUMP)
    {
        if (!map_.detectCollision(marioPos, HAUT))
            mario_.doJump();
        else
            mario_.isFalling(), puts("PASSADE");

    }
    else if (mario_.status() == FALL)
    {
        if (!map_.detectCollision(marioPos, BAS)) mario_.doJump();
        else
            mario_.isOnTheGround();
    }

    if (I.IsMouseButtonDown(sf::Mouse::Right))
    {
        system("cls");
        cout << mario_.x() / 32 << " et " << mario_.y() / 32 << endl;
    }
    /*system("cls");
    cout << mario_.x() / 32 << " et " << mario_.y() / 32 << std::endl;*/
}

bool Map::detectCollision(const sf::Vector2f& pos, int direction)
{
    /*if ((static_cast<int>(pos.y + 1) % 32) != 0 && map_[static_cast<int>(pos.x / 32)][static_cast<int>(pos.y / 32)] != SKY)
        return true;*/

    if (direction == HAUT || direction == BAS)
    {
        if (static_cast<int>(pos.y) % 32 == 0)
        {
            cout << static_cast<int>(pos.x / 32) << " et " << static_cast<int>(pos.y / 32) + (direction == HAUT ? -1 : 1) << endl;
            if (map_[static_cast<int>(pos.x / 32)][static_cast<int>(pos.y / 32) + (direction == HAUT ? -1 : 1)] != SKY)
                    return true;
            /*else if (map_[static_cast<int>(pos.x / 32)][static_cast<int>(pos.y / 32) + (direction == HAUT ? -1 : 1)] == SKY &&
                     map_[static_cast<int>((pos.x + 30) / 32)][static_cast<int>(pos.y / 32) + (direction == HAUT ? -1 : 1)] != SKY)
                return true;*/
        }
    }
    else if (direction == DROITE || direction == GAUCHE)
    {
        if (static_cast<int>(pos.x) % 32 == 0)
        {
            if (map_[static_cast<int>(pos.x / 32) + (direction == DROITE ? 1 : -1)][static_cast<int>(pos.y / 32)] != SKY)
                return true;
            /*else if (map_[static_cast<int>(pos.x / 32) + (direction == DROITE ? 1 : -1)][static_cast<int>(pos.y / 32)] == SKY &&
                     map_[static_cast<int>(pos.x / 32) + (direction == DROITE ? 1 : -1)]
                     [static_cast<int>(pos.y / 32) + (direction == DROITE ? 1 : -1)] != SKY)
                return true;*/
        }
    }
    return false;
}

void createTiles(Vector<sf::Image>& tiles)
{
    sf::Image allTiles;
    if (!allTiles.LoadFromFile("tiles.bmp"))
        std::cerr << "There is an error" << std::endl;

    tiles.resize(7);

    for (Uint i = 0; i < tiles.size(); i++)
    {
        tiles[i].Create(32, 32);
        tiles[i].Copy(allTiles, 0, 0, sf::IntRect(i * 32, 0, (i + 1) * 32, 32));
        tiles[i].CreateMaskFromColor(sf::Color(208, 214, 226));
    }
}
