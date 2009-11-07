#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game() : sf::RenderWindow(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), "Hyper Mario")
{
    _mario = new Mario(&_map);
}

Game::~Game()
{
    delete _mario;
}

void Game::drawAll(void)
{
    sf::View* view = new sf::View;
    view->SetFromRect(_map.getScrolling());

    this->SetView(*view);

    _map.drawMap(*this);
    Draw(*_mario);

    delete view;
}

void Game::evolue(void)
{
    _mario->evolue(_mario->status());
    _map.refreshScrolling(_mario->GetPosition());
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
        getchar();
    //if (input.IsKeyDown(sf::Key::B))
}
