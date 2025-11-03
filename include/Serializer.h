#pragma once
#include "json.hpp"
#include "Platform.h"
#include "TextureManager.h"
#include "Enemy.h"
#include <vector>
#include "TileManager.h"
#include "EnemyManager.h"
#include "Background.h"
#include "Checkpoint.h"
#include <unordered_map>

namespace Serializer {

	nlohmann::json toJSON(Platform& platform, std::string& fileName);
	nlohmann::json savePlatformTiles(const std::vector<TileDef>& platformTiles);
	nlohmann::json savePlatforms(const std::vector<Platform>& platforms);
	nlohmann::json saveEnemySpawnPoints(const std::vector<EnemySpawnPoint>& enemySpawnPoints);
	nlohmann::json saveBackgrounds(const std::vector<Background>& backgrounds);
	nlohmann::json saveCheckpoints(const std::vector<Checkpoint>& checkpoints);

	Platform fromJSON(const nlohmann::json& j, TextureManager& textures);

	void loadPlatforms(const nlohmann::json& j, std::vector<Platform>& platforms, TextureManager& textures, TileManager& tiles);
	void loadEnemySpawnPoints(const nlohmann::json& j, std::vector<EnemySpawnPoint>& enemySpawnPoints);
	void loadBackgrounds(const nlohmann::json& j, std::vector<Background>& backgrounds, TextureManager& textures);
	void loadCheckpoints(const nlohmann::json& j, std::vector<Checkpoint>& checkpoints);
	void loadCheckpoints(const nlohmann::json& j, std::unordered_map<std::string, Checkpoint>& checkpoints);
}