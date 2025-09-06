#pragma once
#include "json.hpp"
#include "Platform.h"
#include "TextureManager.h"
#include "Enemy.h"
#include <vector>

namespace Serializer {

	nlohmann::json toJSON(Platform& platform, std::string& fileName);
	nlohmann::json savePlatforms(std::vector<Platform>& platforms);
	nlohmann::json saveEnemies(std::vector<Enemy>& enemies);
	//nlohmann::json saveLevel(std::vector<Platform>& platforms, std::string& platformTexture);

	Platform fromJSON(const nlohmann::json& j, TextureManager& textures);
	void loadPlatforms(const nlohmann::json& j, std::vector<Platform>& platforms, TextureManager& textures);
	
}