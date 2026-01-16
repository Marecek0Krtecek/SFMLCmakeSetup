#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
	//TextureManager();
	//~TextureManager();

	void loadTexture(const std::string& fileName);

	sf::Texture& get(const std::string& fileName);

private:
	std::map<std::string, sf::Texture> textures = {};
};