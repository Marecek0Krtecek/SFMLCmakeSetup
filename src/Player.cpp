#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeit, float maxHealth, std::unordered_map<std::string, Checkpoint>& checkpoints) :
	animation(texture, imageCount, switchTime),
	checkpoints(checkpoints)
{
	this->speed = speed;
	this->jumpHeit = jumpHeit;
	this->maxHealth = maxHealth;
	this->health = maxHealth;
	
	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	//body.setPosition(checkpoints["spawn"].GetPosition());
	body.setTexture(texture);
}

void Player::Update(float deltaTime) {
	health = std::min(std::max(health, 0.f), maxHealth);	// clamping health

	velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
		//body.move(sf::Vector2f(-0.1f, 0.f));
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;
		//body.move(sf::Vector2f(0.1f, 0.f));

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && canJump) {
		canJump = false;
		if (velocity.x == 0)
			velocity.y = -sqrtf(2.f * (9.81f * gravity) * (jumpHeit * 1.5f));
		else
			velocity.y = -sqrtf(2.f * (9.81f * gravity) * jumpHeit * 0.8f);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && canDash) {
		if (velocity.y < -50.f) {
			velocity.y = 0.f;
		}
		else {
			canDash = false;
			velocity.y += sqrtf(2.f * (9.81f * gravity) * jumpHeit);
		}
	}

	velocity.y += (9.81f * gravity) * deltaTime;

	if (velocity.y > 25.f) {
		canJump = false;
	}

	if (velocity.y < 0.f && !canDash) {
		canDash = true;
	}

	if (velocity.y > 3000.f)
		Die();

	if (velocity.x == 0)
		row = 0;
	else {
		row = 1;

		if (velocity.x > 0.f)
			faceRight = true;
		else
			faceRight = false;
	}

	if (hitDuration > 0.f) {
		hitDuration -= deltaTime;
		row = 2;
	}

	if (row == 0 || row == 2)	//only 4 sprites on these lines out of 8
		animation.Update(row, deltaTime, faceRight, 4);
	else
		animation.Update(row, deltaTime, faceRight, animation.GetImageCount().x);

	body.setTextureRect(animation.uvRect);

	body.move(velocity * deltaTime);
}

void Player::OnCollision(sf::Vector2f direction) {
	if (direction.x > 0.f) {
		//collision on the right
		velocity.x = 0.f;
	}
	else if (direction.x < 0.f) {
		//collision on the left
		velocity.x = 0.f;
	}
	if (direction.y < 0.f) {
		//collision on the bottom
		velocity.y = 0.f;
		canJump = true;
	}
	else if (direction.y > 0.f) {
		//collision on the top
		velocity.y = 0.f;
	}
	
}

void Player::Restrart() {
	body.setPosition(checkpoints["spawn"].GetPosition());
	health = maxHealth;
	velocity = sf::Vector2f();
}

bool Player::Hit(float damage) {
	health -= damage;

	hitDuration = animation.GetSwitchTime() * 4;

	if (health <= 0.f) { 
		Die(); 
		return true;
	}
	return false;
}

void Player::Die() {
	body.setPosition(checkpoints[lastCheckpoint].GetPosition());
	health = maxHealth;
	velocity = sf::Vector2f();
}

float Player::GetDistance(sf::Vector2f otherPosition) const {
	return sqrtf(powf(otherPosition.x - getPosition().x, 2.f) + powf(otherPosition.y - getPosition().y, 2.f));
		//sqrt((x2-x1)^2+(y2-y1)^2)
}