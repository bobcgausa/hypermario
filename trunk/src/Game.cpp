#include "Game.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

#include "Goomba.h"
#include "Flower.h"

Game::Game() : sf::RenderWindow(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "Hyper Mario")
{
    _mario = new Mario(&_map);

    this->loadEnnemys() ;
}

Game::~Game()
{
    delete _mario;

    // Clear list
    std::list<Ennemy *>::iterator it;
    for (it = _ennemys.begin(); it != _ennemys.end(); ++it)
        delete *it;
}

void Game::loadEnnemys(void)
{
    std::ifstream file("media/ennemys/1.enn") ;
    if (!file.is_open())
        std::exit(1);

    while (file.good())
    {
        Ennemy* enn = NULL;
        char c;
        file >> c;

        if (c == 'G')
            enn = new Goomba(&_map);
        else if (c == 'F')
            enn = new Flower(&_map);

        int x, y;
        file >> x >> y;
        enn->SetPosition(x, y);

        _ennemys.push_back(enn);
    }

    file.close();
}

void Game::drawAll(void)
{
    sf::View view;
    view.SetFromRect(_map.getScrolling());

    this->SetView(view);

    _map.drawMap(*this);

    Draw(*_mario);

    if (!_ennemys.empty())
    {
        std::list<Ennemy *>::iterator it;
        for (it = _ennemys.begin(); it != _ennemys.end(); ++it)
            Draw(**it);
    }

}

void Game::evolue(void)
{
    _mario->evolue(_mario->status());
    _map.refreshScrolling(_mario->GetPosition());

    if (!_ennemys.empty())
    {
        std::list<Ennemy *>::iterator it;
        for (it = _ennemys.begin(); it != _ennemys.end(); ++it)
            (*it)->evolue() ;

        for (it = _ennemys.begin(); it != _ennemys.end(); ++it)
        {
            EFFECT e = _mario->isCollide(*it);
            if (e == MARIO_DEAD)
                this->Close();
            else if (e == ENNEMI_DEAD)
            {
                delete *it;
                _ennemys.erase(it);

                // Mario can't kill 2 ennemys at the same time
                break;
            }
        }
    }

}

void Game::checkEvent(void)
{
    const sf::Input& input = this->GetInput();
    sf::Event Event;
    this->GetEvent(Event);

    // close window
    if (Event.Type == sf::Event::Closed)
        this->Close();

    // direction control
    if (input.IsKeyDown(sf::Key::Up))
        if (_mario->status() == ON_THE_GROUND)
            _mario->status() = JUMP;

    if (input.IsKeyDown(sf::Key::Right))
        _mario->evolue(RIGHT);

    if (input.IsKeyDown(sf::Key::Left))
        _mario->evolue(LEFT);

    if (input.IsKeyDown(sf::Key::A))
        this->SetFramerateLimit(10);
    if (input.IsKeyDown(sf::Key::B))
        this->SetFramerateLimit(60);

    //cout << input.GetMouseX() << " et " << input.GetMouseY() << endl, system("cls");
}
