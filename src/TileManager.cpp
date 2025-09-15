#include "TileManager.h"

bool TileManager::loadFromFile(const std::string& fileName) {
	nlohmann::json j;
	std::ifstream read(fileName);
	
	if (read.is_open()) {
		read >> j;

		for (auto& jTile : j["tiles"]) {
			TileDef def;
			def.name = jTile["name"];
			def.textureAdress = jTile["texture"];
			def.rect = sf::IntRect(
				jTile["rect"]["left"].get<int>(),
				jTile["rect"]["top"].get<int>(),
				jTile["rect"]["width"].get<int>(),
				jTile["rect"]["height"].get<int>()
			);

			tileDefs[def.name] = def;
		}

		read.close();

		return true;
	}

	return false;
}

const TileDef* TileManager::getTile(const std::string& name) const {
	auto it = tileDefs.find(name);
	if (it != tileDefs.end())
		return &it->second;

	return nullptr;
}