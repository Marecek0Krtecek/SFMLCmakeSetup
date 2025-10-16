#pragma once
#include <SFML/Graphics.hpp>
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
	void SetName(std::string name) { this->name = name; }

	const sf::Vector2f GetPosition() const { return sf::Vector2f(point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius()); }
	const std::string GetName() const { return name; }
	const sf::FloatRect GetGlobalBounds() const { return point.getGlobalBounds(); }
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