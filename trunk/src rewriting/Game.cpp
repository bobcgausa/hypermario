#include "Game.h"

// Commentataion

Game::Game() : sf::RenderWindow(sf::VideoMode(640, 480), "Hyper Mario")
{
    _mario = new Mario(&_map);
}

Game::~Game()
{
    delete _mario;
}

void Game::drawAll(void)
{
    _map.drawMap(*this);
    Draw(*_mario);
}

void Game::evolue(void)
{

}

void Game::checkEvent(void)
{
    const sf::Input& input = this->GetInput();
    sf::Event Event;
    this->GetEvent(Event);

    if (Event.Type == sf::Event::Closed)
        this->Close();

    if (input.IsKeyDown(sf::Key::Right))
        _mario->evolue(RIGHT);

    if (input.IsKeyDown(sf::Key::Left))
        _mario->evolue(LEFT);

    if (input.IsKeyDown(sf::Key::Up))
        _mario->status() = JUMP;

    if (_mario->status() == JUMP)
        _mario->evolue(JUMP);
    if (_mario->status() == FALL)
        _mario->evolue(FALL);


}
