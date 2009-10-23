#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::Image I;
    if (!I.LoadFromFile("media/map.bmp"))
        return -1;

    Game* G = NULL;
    try
    {
        G = new Game;
    }
    catch (const std::exception& e)
    {
        delete G;
        return EXIT_FAILURE;
    }

    G->loadMap(I);

    while (G->IsOpened())
    {
        G->onEvent();

        // Le bleu correspond au "ciel" du fond
        /** A modifier lorsque le fond et le scrolling sera mis en place **/
        G->Clear(sf::Color::Blue);

        G->drawAll();

        G->Display();

        sf::Sleep(0.001);
    }

    return EXIT_SUCCESS;
}
