#include "Enemy.h"

Enemy::Enemy(const EnemyManager& enemyManager, const EnemySpawnPoint& spawnPoint, TextureManager& textures, int SPID) :
	name(spawnPoint.GetName()),
	animation(&textures.get(enemyManager.getEnemy(spawnPoint.GetName())->textureAdress), enemyManager.getEnemy(spawnPoint.GetName())->imageCount, enemyManager.getEnemy(spawnPoint.GetName())->switchTime),
	speed(enemyManager.getEnemy(spawnPoint.GetName())->speed),
	probe(sf::Vector2f(10.f, 10.f))
{
	body.setSize(sf::Vector2f(50.f, 70.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(spawnPoint.GetPosition());
	body.setTexture(&textures.get(enemyManager.getEnemy(name)->textureAdress));
	body.setTextureRect(enemyManager.getEnemy(name)->rect);

	velocity.x = speed;

	this->spawnPointID = SPID;

	probe.setOrigin(probe.getSize() / 2.f);

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

	//static float timer = 0;
	//timer += deltaTime;

	//if (timer >= 1.f) {
	//	timer -= 1.f;
	//	velocity.x = -velocity.x;
	//}

	velocity.y += (9.81f * gravity) * deltaTime;

	animation.Update(row, deltaTime, faceRight, animation.GetImageCount().x);

	body.setTextureRect(animation.uvRect);

	body.move(velocity * deltaTime);
}

void Enemy::UpdateBehavior(float deltaTime, std::vector<Platform>& platforms) {
	//for (auto& platform : platforms) {
	//	if (getDistance(platform.GetPosition()) <= 200.f) {
	//		foundGround = nextStep(platform.GetGlobalBounds(), deltaTime);
	//		if (foundGround) break;
	//	}
	//}
	foundGround = nextStep(platforms);
	if (!foundGround) velocity.x = -velocity.x;

}

void Enemy::OnCollision(sf::Vector2f direction) {
	if (direction.x > 0.f) {
		//velocity.x = -velocity.x;
		//collision on the right
	}
	else if (direction.x < 0.f) {
		//velocity.x = -velocity.x;
		//collision on the left
	}
	if (direction.y < 0.f) {
		//collision on the top
		velocity.y = 0.f;
	}
	else if (direction.y > 0.f) {
		//collision on the bottom
		velocity.y = 0.f;
	}
}

bool Enemy::OnPlayerColision(Player& player) {
	return player.Hit(1.f);
}

float Enemy::getDistance(sf::Vector2f otherPosition) {
	return sqrtf(powf(otherPosition.x - getPosition().x, 2.f) + powf(otherPosition.y - getPosition().y, 2.f));
}

bool Enemy::nextStep(std::vector<Platform>& platforms) {
	float halfW = GetCollider().GetHalfSize().x;
	float halfH = GetCollider().GetHalfSize().y;

	float offset = 2.f;

	sf::Vector2f futureFeet(getPosition().x + (faceRight ? 1 : -1) * (halfW + offset), getPosition().y + halfH + 5.f);

	probe.setPosition(futureFeet);


	for (auto& platform : platforms) {
		if (abs(platform.GetPosition().x - futureFeet.x) < platform.GetSize().x) {
			sf::Vector2f dir;
			if (getFeetCollider().CheckCollision(platform.GetCollider(), dir, 0.f)) {
				if (dir.y > 0.f) return true;
			}
		}
	}

	return false;
}