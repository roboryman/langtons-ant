#pragma once

#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

using std::unordered_map;
using std::string;

class TextureManager
{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string name);
    public:
        static sf::Texture& GetTexture(string key);
        static void ClearTextures();
};