#ifndef MARIO_H
#define MARIO_H

#include <SFML/Graphics.hpp>

enum { JUMP, FALL, ON_THE_GROUND} ;

class Mario
{
    public:
        Mario();

        void onDraw(sf::RenderWindow& ) ;

        void operator++() ; // Incrémente la position x
        void operator--() ; // Décrémente " "

        float& y() ;
        float& x() ;

        sf::Vector2f pos() const;

        void jump( );
        void doJump() ;

        void isOnTheGround() ;
        void isFalling() ;

        int status() const;

        ~Mario();


    private:
        sf::Image* img_;
        sf::Vector2f pos_;

        int status_;

        double v_y;

        sf::Clock c_;
} ;



#endif // MARIO_H
