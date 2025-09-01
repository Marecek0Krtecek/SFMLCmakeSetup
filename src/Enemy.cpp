#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	velocity.x = speed;

	body.setSize(sf::Vector2f(50.f, 70.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(position);
	body.setTexture(texture);
}

void Enemy::Update(float deltaTime) {
	if (velocity.x == 0.f)
		row = 0;
	else {
		row = 1;
		if (velocity.x > 0.f)
			faceRight = true;
		else
			faceRight = false;
	}

	velocity.y += (9.81f * gravity) * deltaTime;

	animation.Update(row, deltaTime, faceRight, animation.GetImageCount().x);

	body.setTextureRect(animation.uvRect);

	body.move(velocity * deltaTime);
}

void Enemy::OnCollision(sf::Vector2f direction) {
	if (direction.x > 0.f) {
		velocity.x = -velocity.x;
		//collision on the right
	}
	else if (direction.x < 0.f) {
		velocity.x = -velocity.x;
		//collision on the left
	}
	if (direction.y < 0.f) {
		//collision on the bottom
		velocity.y = 0.f;
	}
	else if (direction.y > 0.f) {
		//collision on the top
		velocity.y = 0.f;
	}
}

bool Enemy::OnPlayerColision(Player& player) {
	player.health -= 1.f;

	if (player.health <= 0.f)
		return KillPlayer(player);

	return false;
}

bool Enemy::KillPlayer(Player& player) {
	player.Restrart();
	return true;
}