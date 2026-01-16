#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "json.hpp"
#include <fstream>

struct TileDef
{
	std::string name;
	sf::IntRect rect;
	std::string textureAdress;
};

class TileManager
{
public:
	//TileManager();
	//~TileManager();

	bool loadFromFile(const std::string& fileName);

	const TileDef* getTile(const std::string& name) const;

	const std::map<std::string, TileDef>& getAllTiles() const { return tileDefs; }

private:
	std::map<std::string, TileDef> tileDefs;
};