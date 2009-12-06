#include <SFML/Graphics.hpp>
#include "Game.h"

int main(void)
{
    Game game;

    game.UseVerticalSync(true);

    while (game.IsOpened())
    {
        game.checkEvent();

        game.evolue();

        game.Clear(sf::Color::Blue);

        game.drawAll();

        game.Display();
        sf::Sleep(0.001);
    }

    return EXIT_SUCCESS;
}
