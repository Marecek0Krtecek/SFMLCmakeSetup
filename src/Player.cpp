#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeit) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeit = jumpHeit;
	
	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(sf::Vector2f(0.f, -50.f));
	body.setTexture(texture);
}

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeit, float maxHealth) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeit = jumpHeit;
	this->maxHealth = maxHealth;
	
	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(sf::Vector2f(0.f, -50.f));
	body.setTexture(texture);
}

Player::Player(sf::Vector2f size, sf::Texture* texture):
	animation(nullptr, sf::Vector2u(0, 0), 0.f)
{
	body.setSize(size);
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(sf::Vector2f(0.f, 0.f));
	body.setTexture(texture);
}

void Player::Update(float deltaTime) {
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
			velocity.y = -sqrtf(2.f * (9.81f * gravity) * (jumpHeit * 1.5));
		else
			velocity.y = -sqrtf(2.f * (9.81f * gravity) * jumpHeit);
			
	}

	velocity.y += (9.81f * gravity) * deltaTime;

	if (velocity.y > 25.f)
		canJump = false;

	if (velocity.x == 0)
		row = 0;
	else {
		row = 2;

		if (velocity.x > 0.f)
			faceRight = true;
		else
			faceRight = false;
	}

	if (row == 0 || row == 6 || row == 7)	//only 4 sprites on these lines out of 8
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
	body.setPosition(sf::Vector2f(0.f, -50.f));
	health = maxHealth;
}

float Player::GetDistance(sf::Vector2f otherPosition) {
	return sqrtf(powf(otherPosition.x - getPosition().x, 2.f) + powf(otherPosition.y - getPosition().y, 2.f));
		//sqrt((x2-x1)^2+(y2-y1)^2)
}