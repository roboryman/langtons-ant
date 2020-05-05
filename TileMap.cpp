#include <string>
#include <fstream>
#include <sstream>
#include "TileMap.hpp"


TileMap::TileMap()
{
    FillColorMap("resources/colors.txt");
}

void TileMap::FillColorMap(std::string path)
{
    std::ifstream colors(path);

    if(colors.is_open())
    {
        std::string color;
        int i = 0;
        while(getline(colors, color))
        {
            std::istringstream istream(color);
            std::string r, g, b;
            std::getline(istream, r, ',');
            std::getline(istream, g, ',');
            std::getline(istream, b, ',');
            ColorMap.emplace(i++, sf::Color(std::stoi(r), std::stoi(g), std::stoi(b), 255));
        }
        colors.close();
    }
}

void TileMap::UpdateTile(int index, std::vector<short> &tileData)
{
    int tileType = tileData.at(index);
    sf::Vertex *quad = &m_vertices[ index * 4];

    quad[0].color = ColorMap[tileType];
    quad[1].color = ColorMap[tileType];
    quad[2].color = ColorMap[tileType];
    quad[3].color = ColorMap[tileType];
}

bool TileMap::load(float tileSize, int size, std::vector<short> &tileData)
{
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(size * size * 4);

    for (unsigned int i = 0; i < size; ++i)
    {
        for (unsigned int j = 0; j < size; ++j)
        {
            int tileType = tileData[i + j*size];
            sf::Vertex* quad = &m_vertices[(i + j*size) * 4];

            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

            quad[0].color = ColorMap[tileType];
            quad[1].color = ColorMap[tileType];
            quad[2].color = ColorMap[tileType];
            quad[3].color = ColorMap[tileType];
        }
    }
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}