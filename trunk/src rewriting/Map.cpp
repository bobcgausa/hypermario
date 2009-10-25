#include "Map.h"

Map::Map()
{
    sf::Image map, tiles;

    map.LoadFromFile("media/map.bmp");
    m_tiles.resize(map.GetWidth(), std::vector<s_Tiles>(map.GetHeight()));

    tiles.LoadFromFile("media/tiles.bmp");
    m_img_tiles.resize(tiles.GetWidth() / 32 + 1);

    const sf::Color mask(208, 214, 226);

    for (int i = 0; i < (m_img_tiles.size() - 1); ++i)
    {
        m_img_tiles[i].Create(32, 32);
        m_img_tiles[i].Copy(tiles, 0, 0, sf::IntRect(i * 32, 0, (i + 1) * 32, 32));
        m_img_tiles[i].CreateMaskFromColor(mask);
    }

    m_img_tiles[m_img_tiles.size() - 1].Create(32, 32, sf::Color(0, 0, 255));

    for (unsigned int i = 0; i < map.GetWidth(); ++i)
    {
        for (unsigned int j = 0; j < map.GetHeight(); ++j)
        {
            TYPE type;

            if (map.GetPixel(i, j) == sf::Color::Blue)
                type = SKY;

            else if (map.GetPixel(i, j) == sf::Color::Red)
                type = BOX;

            else if (map.GetPixel(i, j) == sf::Color::Magenta)
                type = WALL;

            else if (map.GetPixel(i, j) == sf::Color::Color(255, 102, 0))
                type = GROUND;

            else if (map.GetPixel(i, j) == sf::Color::Color(34, 255, 29))
                type = TUBE_HEADER1;

            else if (map.GetPixel(i, j) == sf::Color::Color(155, 255, 54))
                type = TUBE_HEADER2;

            else if (map.GetPixel(i, j) == sf::Color::Color(34, 231, 29))
                type = TUBE_BOTTOM1;

            else if (map.GetPixel(i, j) == sf::Color::Color(155, 231, 54))
                type = TUBE_BOTTOM2;

            m_tiles[i][j].type = type;
            m_tiles[i][j].spr.SetImage(m_img_tiles[type]);

            m_tiles[i][j].spr.SetX(static_cast<float>(i * 32));
            m_tiles[i][j].spr.SetY(static_cast<float>(j * 32));
        }
    }
}

void Map::drawMap(sf::RenderWindow& game)
{
    for (int i = 0; i < m_tiles.size(); ++i)
    {
        for (int j = 0; j < m_tiles[i].size(); ++j)
        {
            game.Draw(m_tiles[i][j].spr);
        }
    }
}
