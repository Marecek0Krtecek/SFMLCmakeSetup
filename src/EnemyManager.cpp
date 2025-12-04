#include "EnemyManager.h"

EnemySpawnPoint::EnemySpawnPoint(const std::string& name, sf::Vector2f position) :
	name(name),
	point(16.f)
{
	point.setPosition(position.x - point.getRadius(), position.y - point.getRadius());
	point.setFillColor(sf::Color::Red);
}

bool EnemyManager::loadFromFile(const std::string& fileName) {
	nlohmann::json j;
	std::ifstream read(fileName);
	
	if (read.is_open()) {
		read >> j;

		for (auto& jEnemy : j["enemies"]) {
			EnemyDef def;

			def.name = jEnemy["name"].get<std::string>();
			def.textureAdress = jEnemy["texture"].get<std::string>();

			def.rect = sf::IntRect(
				jEnemy["rect"]["left"].get<int>(),
				jEnemy["rect"]["top"].get<int>(),
				jEnemy["rect"]["width"].get<int>(),
				jEnemy["rect"]["height"].get<int>()
			);

			def.imageCount = sf::Vector2u(
				jEnemy["imageCount"]["x"].get<int>(),
				jEnemy["imageCount"]["y"].get<int>()
			);
			def.switchTime = jEnemy["switchTime"].get<float>();
			def.speed = jEnemy["speed"].get<float>();

			enemyDefs[def.name] = def;
		}

		read.close();

		return true;
	}
	else {
		std::cout << "File \"" << fileName << "\" was not found!";
	}

	return false;
}

const EnemyDef* EnemyManager::getEnemy(const std::string& name) const {
	auto it = enemyDefs.find(name);
	if (it != enemyDefs.end())
		return &it->second;

	return nullptr;
}