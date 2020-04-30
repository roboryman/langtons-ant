#include "TextureManager.hpp"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string key)
{
    string fileName = "images/" + key + ".png";
    textures[key].loadFromFile(fileName);
}

sf::Texture& TextureManager::GetTexture(string key)
{
    if(textures.find(key) == textures.end())
    {
        LoadTexture(key);
    }
    return textures[key];
}

void TextureManager::ClearTextures()
{
    textures.clear();
}