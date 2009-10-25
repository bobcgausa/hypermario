#include "Game.h"

Game::Game() : sf::RenderWindow(sf::VideoMode(640, 480), "Hyper Mario")
{

}

Game::~Game()
{

}

void Game::drawAll(void)
{
    m_map.drawMap(*this);
    Draw(m_mario);
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
        m_mario.Move(1, 0);
}
