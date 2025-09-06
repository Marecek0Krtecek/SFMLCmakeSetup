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

nlohmann::json Serializer::savePlatforms(std::vector<Platform>& platforms) {
	nlohmann::json j;
	j["levelName"] = "TestLevel";
	//j["background"]
	//j["music"]
	j["playerSpawn"] = { {"x", 0.f},{"y",-50.f} };
	j["platforms"] = nlohmann::json::array();
	for (auto& platform : platforms) {
		j["platforms"].push_back(
			{
				{"x", platform.GetPosition().x},
				{"y", platform.GetPosition().y},
				{"width", platform.GetSize().x},
				{"height", platform.GetSize().y},
				{"texture", platform.GetTexture()},
				{"uvRect", 
					{
						{"height", platform.GetUvRect().height},
						{"width", platform.GetUvRect().width},
						{"top", platform.GetUvRect().top},
						{"left", platform.GetUvRect().left}
					}
				}
			}
		);
	}
	//j["enemies"]

	return j;
}

nlohmann::json Serializer::saveEnemies(std::vector<Enemy>& enemies) {
	nlohmann::json j;
	j["levelName"] = "TestLevel";
	//j["background"]
	//j["music"]
	j["playerSpawn"] = { {"x", 0.f},{"y",-50.f} };
	//j["platforms"] = nlohmann::json::array();
	j["enemies"] = nlohmann::json::array();
	for (auto& enemy : enemies) {
		j["enemies"].push_back(
			{
				{"x", enemy.getPosition().x},
				{"y", enemy.getPosition().y},
				{"width", enemy.GetSize().x},
				{"height", enemy.GetSize().y},
				{"texture", enemy.GetTexture()},
				{"speed", enemy.GetSpeed()},
				{"switchTime", enemy.GetSwitchTime()},
				{"imageCount",
					{
						{"x", enemy.GetImageCount().x},
						{"y", enemy.GetImageCount().y}
					}
				}
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

void Serializer::loadPlatforms(const nlohmann::json& j, std::vector<Platform>& platforms, TextureManager& textures) {
	for (const auto& jPlatform : j["platforms"]) {
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
				jPlatform["texture"].get<std::string>()
			),
			sf::IntRect(/*left top width height*/
				jPlatform["uvRect"]["left"].get<int>(),
				jPlatform["uvRect"]["top"].get<int>(),
				jPlatform["uvRect"]["width"].get<int>(),
				jPlatform["uvRect"]["height"].get<int>()
			),
			jPlatform["texture"].get<std::string>()
		));
	}
}