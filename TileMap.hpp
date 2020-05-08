#pragma once


#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>


/**
 * TileMap
 * Defines a drawable and transformable TileMap using a VertexArray.
 */
class TileMap : public sf::Drawable, public sf::Transformable
{
    std::unordered_map<int, sf::Color> ColorMap;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    // Draw our TileMap to a Render Target.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Clears the Color Map and fills it with RGB colors on the disk.
    void FillColorMap(std::string path);

    public:
        // Construct a TileMap.
        TileMap();

        // Setup the TileMap in accordance with existing data.
        bool Setup(float tileSize, int size, std::vector<short> &tileData);

        // Update a particular tile on the TileMap.
        void UpdateTile(int index, std::vector<short> &tileData);
};