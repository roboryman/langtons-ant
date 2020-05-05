#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

class TileMap : public sf::Drawable, public sf::Transformable {

    std::unordered_map<int, sf::Color> ColorMap;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void FillColorMap(std::string path);

    public:
        TileMap();
        bool load(float tileSize, int size, std::vector<short> &tileData);
        void UpdateTile(int index, std::vector<short> &tileData);
};