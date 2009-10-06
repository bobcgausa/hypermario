#ifndef MAP_H
#define MAP_H

#include "Vector.h"

#include <SFML\Graphics.hpp>

typedef unsigned int Uint;

const int SKY = 33;

enum { GAUCHE, DROITE, HAUT, BAS } ;


class Map
{
    public:
        Map();
        Map(const sf::Image& ) ;
        void createFrom(const sf::Image& ) ;
        void onDraw(sf::RenderWindow&, Vector<sf::Image>& ) ;

        bool detectCollision(const sf::Vector2f& , int = -1) ;

        int height() const;
        int width() const;

        int& operator()(int, int ) ;

        ~Map();

    private:
        int** map_;
        int height_; int width_;

};

#endif // MAP_H
