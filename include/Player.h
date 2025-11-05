#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Animation.h"
#include "Checkpoint.h"
#include <unordered_map>

class Player {
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeit, float maxHealth, std::unordered_map<std::string, Checkpoint>& checkpoints);

	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);
	void Restrart();
	bool Hit(float damage);

	void draw(sf::RenderWindow& window) { window.draw(body); }
	void setScale(sf::Vector2f scale) { body.setScale(scale); }
	void setPosition(sf::Vector2f position) { body.setPosition(position); }
	void setPosition(float x, float y) { body.setPosition(x, y); }

	sf::Vector2f getPosition() const { return body.getPosition(); }
	sf::Vector2f GetVelocity() const { return velocity; }
	sf::Vector2f GetSize() const { return body.getSize(); }
	Collision GetCollider() { return Collision(body); }
	float GetDistance(sf::Vector2f objectPosition) const;
	std::string GetLastCheckpoint() const { return lastCheckpoint; }

private:
	void Die();


public:
	float gravity = 50.f;
	float health = 1.f;

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row = 0;
	float speed = 500;
	bool faceRight = true;

	sf::Vector2f velocity;
	bool canJump = false;
	float jumpHeit = 100.f;
	float maxHealth = 1.f;
	
	std::string lastCheckpoint = "spawn";
	std::unordered_map<std::string, Checkpoint>& checkpoints;
};