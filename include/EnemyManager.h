#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <map>
#include "json.hpp"
#include <fstream>

struct EnemyDef
{
	std::string name;
	sf::IntRect rect;
	std::string textureAdress;
	sf::Vector2u imageCount;
	float switchTime;
	float speed;
};

class EnemySpawnPoint
{
public:
	EnemySpawnPoint(const std::string& name, sf::Vector2f position);

	void draw(sf::RenderWindow& window) { window.draw(point); }

	void SetPosition(const sf::Vector2f& position) { point.setPosition(position.x - point.getRadius(), position.y - point.getRadius()); }

	sf::Vector2f GetPosition() { return sf::Vector2f(point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius()); }
	std::string GetName() { return name; }
private:
	std::string name;
	sf::CircleShape point;
};

class EnemyManager
{
public:
	//EnemyManager();
	//~EnemyManager();

	bool loadFromFile(const std::string& fileName);

	const EnemyDef* getEnemy(const std::string& name) const;

	const std::map<std::string, EnemyDef>& getAllEnemies() const { return enemyDefs; }

private:
	std::map<std::string, EnemyDef> enemyDefs;
};