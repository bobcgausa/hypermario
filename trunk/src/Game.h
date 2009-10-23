#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

enum { LEFT, RIGHT, UP, DOWN} ;

const int SIZE_BLOC = 32;
const int SCREEN_WIDHT = 640;
const int SCREEN_HEIGHT = 480;

const sf::Color mask(208, 214, 226);

#include "Map.h"
#include "Mario.h"


class Game : public sf::RenderWindow
{
    public:
        Game();
        virtual ~Game();

        void loadMap(const sf::Image& ) ;
        void createTiles() ;
        void drawAll() ;

        void onEvent() ;



    private:
        void drawMario() ;
        void drawMap() ;

        Map map_;
        std::vector<sf::Image> tiles_;
        Mario* mario_;
        sf::Clock clock_;
        double lastTime;
};

#endif // GAME_H
