#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
public:
	//TextureManager();
	//~TextureManager();

	sf::Texture& get(const std::string& fileName);

private:
	std::map<std::string, sf::Texture> textures = {};
};