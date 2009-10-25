#include "Game.h"

Game::Game() : sf::RenderWindow(sf::VideoMode(640, 480), "Hyper Mario")
{
    m_mario = new Mario(&m_map);
}

Game::~Game()
{
    delete m_mario;
}

void Game::drawAll(void)
{
    m_map.drawMap(*this);
    Draw(*m_mario);
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
        m_mario->evolue(RIGHT);

    if (input.IsKeyDown(sf::Key::Left))
        m_mario->evolue(LEFT);

    if (input.IsKeyDown(sf::Key::Up))
        m_mario->evolue(JUMP);
}
