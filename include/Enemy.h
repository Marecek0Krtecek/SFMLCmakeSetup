#pragma once
#include "Collision.h"
#include "Animation.h"
#include "Player.h"
#include <string>
#include "EnemyManager.h"
#include "TextureManager.h"
#include "Platform.h"

class Enemy
{
public:
	Enemy(const EnemyManager& enemyManager, const EnemySpawnPoint& spawnPoint, TextureManager& textures, int SPID);

	void Update(float deltaTime);
	void UpdateBehavior(float deltaTime, std::vector<Platform>& platforms, Player& player);
	void OnCollision(sf::Vector2f direction);
	bool OnPlayerColision(Player& player);

	void draw(sf::RenderWindow& window);
	
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
	float getDistance(sf::Vector2f otherPosition);
	sf::Vector2f getDirectionOfOther(sf::Vector2f otherPosition) const;
	sf::Vector2f getDirectionOfOtherN(sf::Vector2f otherPosition) const;
	Collision getFeetCollider() { return Collision(probe); }

	bool nextStep(std::vector<Platform>& platforms);
	void lookForPlayer(Player& player);


public:
	float gravity = 50.f;
	int spawnPointID = -1;
	

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row = 1;
	float speed = 500;
	bool faceRight = true;

	sf::Vector2f velocity;

	std::string name;

	//AI stuff
	bool foundGround = false;
	EnemyState state = Idle;
	float stayIdle = rand() % 3 + 3.f;
	float patrol = rand() % 5 + 6.f;
	float idleTimer = 0.f;
	float patrolTimer = 0.f;

	float agroRange = 256.f;

	//Preview stuff
	sf::RectangleShape probe;
#if PRODUCTION_BUILD == 0
	sf::CircleShape agro;
#endif
};
