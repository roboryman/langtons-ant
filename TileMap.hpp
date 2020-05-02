#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

using std::vector;

class TileMap : public sf::Drawable, public sf::Transformable {

    std::unordered_map<int, sf::Color> ColorMap;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        TileMap();
        bool update(float tileSize, int size, vector<short> &tileData);
        void UpdateTile(int index, vector<short> &tileData);
};