#pragma once
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

	void draw(sf::RenderWindow& window);
	void setScale(sf::Vector2f scale) { body.setScale(scale); }
	void setPosition(sf::Vector2f position) { body.setPosition(position); }
	void setPosition(float x, float y) { body.setPosition(x, y); }
	void setCheckpoint(std::string checkpoint) { lastCheckpoint = checkpoint; }

	sf::Vector2f getPosition() const { return body.getPosition(); }
	sf::FloatRect getGlobalBounds() const { return body.getGlobalBounds(); }
	sf::Vector2f getScale() const { return body.getScale(); }
	sf::Vector2f GetVelocity() const { return velocity; }
	sf::Vector2f GetSize() const { return body.getSize(); }
	Collision GetCollider() { return Collision(body); }
	float GetDistance(sf::Vector2f objectPosition) const;
	std::string GetLastCheckpoint() const { return lastCheckpoint; }
	float GetMaxHealth() const { return maxHealth; }

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
	float hitDuration = 0.f;

	sf::Vector2f velocity;
	bool canJump = false;
	bool canDash = false;
	float jumpHeit = 100.f;
	float maxHealth = 1.f;
	
	std::string lastCheckpoint = "spawn";
	std::unordered_map<std::string, Checkpoint>& checkpoints;

	sf::RectangleShape HPBar;
	sf::RectangleShape HPShow;
};