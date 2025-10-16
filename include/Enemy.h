#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Animation.h"
#include "Player.h"
#include <string>
#include "EnemyManager.h"
#include "TextureManager.h"

class Enemy
{
public:
	Enemy(const EnemyManager& enemyManager, const EnemySpawnPoint& spawnPoint, TextureManager& textures);

	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);
	bool OnPlayerColision(Player& player);

	void draw(sf::RenderWindow& window) { window.draw(body); }
	
	void setScale(sf::Vector2f scale) { body.setScale(scale); }
	void SetDirection(sf::Vector2f direction) { velocity = sf::Vector2f(velocity.x * direction.x, velocity.y * direction.y); }

	sf::Vector2f GetSize() const { return body.getPosition(); }
	sf::Vector2f getPosition() const { return body.getPosition(); }
	sf::Vector2f GetVelocity() const { return velocity; }
	Collision GetCollider() { return Collision(body); }
	sf::Vector2u GetImageCount() const { return animation.GetImageCount(); }
	float GetSwitchTime() const { return animation.GetSwitchTime(); }
	float GetSpeed() const { return speed; }
	std::string GetEnemyName() const { return name; }

private:
	bool KillPlayer(Player& player);

public:
	float gravity = 50.f;

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row = 0;
	float speed = 500;
	bool faceRight = true;

	sf::Vector2f velocity;

	std::string name;
};
