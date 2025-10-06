#include "Serializer.h"

nlohmann::json Serializer::toJSON(Platform& platform, std::string& fileName) {
	return {
		{"x", platform.GetPosition().x},
		{"y", platform.GetPosition().y},
		{"width", platform.GetSize().x},
		{"height", platform.GetSize().y},
		{"texture", fileName}
	};
}

nlohmann::json Serializer::savePlatformTiles(const std::vector<TileDef>& platformTiles) {
	nlohmann::json j;
	j["platformTiles"] = nlohmann::json::array();
	for (const auto& tile : platformTiles) {
		j["platformTiles"].push_back(
			{
				{"name", tile.name},
				{"rect",
					{
						{"height", tile.rect.height},
						{"width", tile.rect.width},
						{"top", tile.rect.top},
						{"left", tile.rect.left}
					}
				},
				{"adress", tile.textureAdress}
			}
		);
	}
	return j;
}

nlohmann::json Serializer::savePlatforms(const std::vector<Platform>& platforms) {
	nlohmann::json j;
	//j["levelName"] = "TestLevel";
	//j["background"]
	//j["music"]
	//j["playerSpawn"] = { {"x", 0.f},{"y",-50.f} };
	j["platformCount"] = platforms.size();
	j["platforms"] = nlohmann::json::array();
	for (auto& platform : platforms) {
		j["platforms"].push_back(
			{
				{"x", platform.GetPosition().x},
				{"y", platform.GetPosition().y},
				{"width", platform.GetSize().x},
				{"height", platform.GetSize().y},
				{"tile", platform.GetTexture()}
			}
		);
	}
	//j["enemies"]

	return j;
}

nlohmann::json Serializer::saveEnemySpawnPoints(const std::vector<EnemySpawnPoint>& enemySpawnPoints) {
	nlohmann::json j;
	//j["levelName"] = "TestLevel";
	//j["background"]
	//j["music"]
	//j["playerSpawn"] = { {"x", 0.f},{"y",-50.f} };
	//j["platforms"] = nlohmann::json::array();
	j["enemyCount"] = enemySpawnPoints.size();
	j["enemySpawnPoints"] = nlohmann::json::array();
	for (const auto& enemy : enemySpawnPoints) {
		j["enemySpawnPoints"].push_back(
			{
				{ "type", enemy.GetName() },
				{ "x", enemy.GetPosition().x },
				{ "y", enemy.GetPosition().y }
			}
		);
	}

	return j;

} 

Platform Serializer::fromJSON(const nlohmann::json& j, TextureManager& textures) {
	return Platform(
		sf::Vector2f(
			j["width"].get<float>(),
			j["height"].get<float>()
		),
		sf::Vector2f(
			j["x"].get<float>(),
			j["y"].get<float>()
		)//,
		//textures.get(j["texture"].get<std::string>())
	);
}

void Serializer::loadPlatforms(const nlohmann::json& j, std::vector<Platform>& platforms, TextureManager& textures, TileManager& tiles) {
	if (j.contains("platforms")) {
		for (const auto& jPlatform : j["platforms"]) {
			auto* tile = tiles.getTile(jPlatform["tile"].get<std::string>());
			platforms.push_back(Platform(
				sf::Vector2f(
					jPlatform["width"].get<float>(),
					jPlatform["height"].get<float>()
				),
				sf::Vector2f(
					jPlatform["x"].get<float>(),
					jPlatform["y"].get<float>()
				),
				&textures.get(
					tile->textureAdress
				),
				tile->rect,
				tile->name
			));
		}
	}

	if (j.contains("platform")) {
		const auto& jPatform = j["platform"];
		if (jPatform.contains("platformCount")) {
			platforms.reserve(jPatform["platformCount"].get<size_t>());
		}
		if (jPatform.contains("platforms")) {
			for (const auto& jPlatform : jPatform["platforms"]) {
				auto* tile = tiles.getTile(jPlatform["tile"].get<std::string>());
				platforms.push_back(Platform(
					sf::Vector2f(
						jPlatform["width"].get<float>(),
						jPlatform["height"].get<float>()
					),
					sf::Vector2f(
						jPlatform["x"].get<float>(),
						jPlatform["y"].get<float>()
					),
					&textures.get(
						tile->textureAdress
					),
					tile->rect,
					tile->name
				));
			}

		}
	}
}

void Serializer::loadEnemySpawnPoints(const nlohmann::json& j, std::vector<EnemySpawnPoint>& enemySpawnPoints) {
	if (j.contains("enemy")) {
		const auto& jEnemy = j["enemy"];
		if (jEnemy.contains("enemyCount")) {
			enemySpawnPoints.reserve(jEnemy["enemyCount"].get<size_t>());
		}
		if (jEnemy.contains("enemySpawnPoints")) {
			for (const auto& jEnemySP : jEnemy["enemySpawnPoints"]) {
				enemySpawnPoints.push_back(EnemySpawnPoint(
					jEnemySP["type"].get<std::string>(),
					sf::Vector2f(
						jEnemySP["x"].get<float>(),
						jEnemySP["y"].get<float>()
					)
				));
			}
		}
	}
}