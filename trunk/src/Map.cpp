#include "Map.h"

#include <iostream>
#include <SFML\Graphics.hpp>

Map::Map()
{

}

Map::Map(const sf::Image& Map)
{
    createFrom(Map);
}

void Map::createFrom(const sf::Image& Map)
{
    Vector<sf::Color> colorToTile;
    colorToTile.resize(7);
    colorToTile[0] = sf::Color(255, 0, 0);
    colorToTile[1] = sf::Color(255, 102, 0);
    colorToTile[2] = sf::Color(255, 0, 255);
    colorToTile[3] = sf::Color(34, 255, 29);
    colorToTile[4] = sf::Color(155, 255, 54);
    colorToTile[5] = sf::Color(34, 231, 29);
    colorToTile[6] = sf::Color(155, 231, 54);
    // Partie du dessus à changer

    width_ = Map.GetWidth(), height_ = Map.GetHeight();

    map_ = new int*[width_]; // Tableau de int 2D faisant la taille de la map
    for (int i = 0; i < width_; ++i)
        map_[i] = new int[height_];

    for (int i = 0; i < width_; ++i)
    {
        for (int j = 0; j < height_; ++j)
        {
            sf::Color toGet = Map.GetPixel(i, j); // Recuperation des pixels de la map

            if (toGet == sf::Color::Blue)
            {
                map_[i][j] = SKY;
            }
            else
            {
                for (Uint k = 0; k < colorToTile.size(); ++k)
                {
                    if (colorToTile[k] == toGet)
                    {
                        map_[i][j] = k;
                        break;
                    }
                }
            }
        }
    }
}

void Map::onDraw(sf::RenderWindow& App, Vector<sf::Image>& tiles)
{
    for (int i = 0; i < width_; ++i)
    {
        for (int j = 0; j < height_; ++j)
        {
            if (map_[i][j] != SKY)
            {
                sf::Sprite* s = new sf::Sprite;

                s->SetImage( tiles[ map_[i][j] ] ); // On recupere le tile qui correspond
                s->SetPosition(i * 32, j * 32);

                App.Draw(*s);

                delete s;
            }
        }
    }
}

int& Map::operator()(int n, int n2)
{
    return map_[n][n2];
}

int Map::width() const
{
    return width_;
}

int Map::height() const
{
    return height_;
}

Map::~Map()
{
    for (int i = 0; i < width_; i++)
        delete map_[i];
    delete[] map_;
}
