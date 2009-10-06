#include <SFML/Graphics.hpp>
#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Game.h"


int main()
{
    sf::Image I;
    if (!I.LoadFromFile("map.bmp"))
        return -1;

    Game* G = new Game;
    G->loadMap(I);

    while (G->IsOpened())
    {
        G->onEvent();

        G->Clear(sf::Color::Blue);

        G->drawAll();

        G->Display();

        sf::Sleep(0.001);
    }

    delete G;

    return 0;
}
