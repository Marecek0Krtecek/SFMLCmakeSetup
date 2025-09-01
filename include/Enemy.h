#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Animation.h"
#include "Player.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);

	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);
	bool OnPlayerColision(Player& player);

	void draw(sf::RenderWindow& window) { window.draw(body); }
	void setScale(sf::Vector2f scale) { body.setScale(scale); }
	void SetDirection(sf::Vector2f direction) { velocity = sf::Vector2f(velocity.x * direction.x, velocity.y * direction.y); }

	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Vector2f GetVelocity() { return velocity; }
	Collision GetCollider() { return Collision(body); }

private:
	bool KillPlayer(Player& player);
public:
	float gravity = 50.f;
	bool* thisPlatformHasMe = nullptr;

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row = 0;
	float speed = 500;
	bool faceRight = true;

	sf::Vector2f velocity;
};
