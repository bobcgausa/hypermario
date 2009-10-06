#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Map.h"
#include "Mario.h"

void createTiles(Vector<sf::Image>& ) ;

class Game : public sf::RenderWindow
{
    public:
        Game();
        virtual ~Game();
        void loadMap(const sf::Image& ) ;
        void drawAll() ;


        void drawMario() ;
        void drawMap() ;

        void onEvent() ;



    private:
        Map map_;
        Vector<sf::Image> tiles_;
        Mario mario_;
        sf::Clock clock_;
        double lastTime;


};

#endif // GAME_H
