#include "Enemy.h"

Enemy::Enemy(const EnemyManager& enemyManager, const EnemySpawnPoint& spawnPoint, TextureManager& textures, int SPID) :
	name(spawnPoint.GetName()),
	animation(&textures.get(enemyManager.getEnemy(spawnPoint.GetName())->textureAdress), enemyManager.getEnemy(spawnPoint.GetName())->imageCount, enemyManager.getEnemy(spawnPoint.GetName())->switchTime),
	speed(enemyManager.getEnemy(spawnPoint.GetName())->speed),
#if PRODUCTION_BUILD == 0
	agro(agroRange),
#endif
	probe(sf::Vector2f(10.f, 10.f))
{
	body.setSize(sf::Vector2f(50.f, 70.f));
	body.setOrigin(sf::Vector2f(body.getSize() / 2.f));
	body.setPosition(spawnPoint.GetPosition());
	body.setTexture(&textures.get(enemyManager.getEnemy(name)->textureAdress));
	body.setTextureRect(enemyManager.getEnemy(name)->rect);

	//velocity.x = speed;

	this->spawnPointID = SPID;

	probe.setOrigin(probe.getSize() / 2.f);

#if PRODUCTION_BUILD == 0
	agro.setFillColor(sf::Color::Transparent);
	agro.setOutlineColor(sf::Color::Red);
	agro.setOutlineThickness(5.f);
#endif
}

void Enemy::Update(float deltaTime) {
	unsigned int amount = animation.GetImageCount().x;
	if (velocity.x == 0.f)
		amount = 2;
	else {
		//row = 1;
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

	animation.Update(row, deltaTime, faceRight, amount);

	body.setTextureRect(animation.uvRect);

	body.move(velocity * deltaTime);
#if PRODUCTION_BUILD == 0
	agro.setPosition(getPosition().x - agro.getRadius(), getPosition().y - agro.getRadius());
#endif
}

void Enemy::UpdateBehavior(float deltaTime, std::vector<Platform>& platforms, Player& player) {
	
	foundGround = nextStep(platforms);
	lookForPlayer(player);

	switch (state) {
	case Idle:
		idleTimer += deltaTime;
		velocity.x = 0.f;

		if (idleTimer >= stayIdle) {
			idleTimer = 0.f;
			patrolTimer = 0.f;

			state = Patrol;

			velocity.x = (faceRight ? -speed : speed);

			faceRight = !faceRight;

			if (!foundGround) velocity.x = -velocity.x;
		}

		break;
	case Patrol:
		patrolTimer += deltaTime;

		if (patrolTimer >= patrol) {
			patrolTimer = 0.f;
			idleTimer = 0.f;

			state = Idle;

			velocity.x = 0.f;
		}
	
		if (!foundGround) velocity.x = -velocity.x;

		break;
	case Chase:
		if (!foundGround && getDirectionOfOtherN(player.getPosition()).x == (faceRight ? 1 : -1)) velocity.x = 0;
		else if (!foundGround && getDirectionOfOtherN(player.getPosition()).x != (faceRight ? 1 : -1)) velocity.x = speed * (!faceRight ? 1 : -1);

		break;
	}


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

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(body);
#if PRODUCTION_BUILD == 0
	//window.draw(probe);
	//window.draw(agro);
#endif
}

bool Enemy::OnPlayerColision(Player& player) {
	return player.Hit(1.f);
}

float Enemy::getDistance(sf::Vector2f otherPosition) {
	return sqrtf(powf(otherPosition.x - getPosition().x, 2.f) + powf(otherPosition.y - getPosition().y, 2.f));
}

sf::Vector2f Enemy::getDirectionOfOther(sf::Vector2f otherPosition) const {
	sf::Vector2f dir;
	dir.x = otherPosition.x - getPosition().x;
	dir.y = otherPosition.y - getPosition().y;
	
	return dir;
}

sf::Vector2f Enemy::getDirectionOfOtherN(sf::Vector2f otherPosition) const {
	sf::Vector2f dir;
	dir.x = (otherPosition.x - getPosition().x) / abs(otherPosition.x - getPosition().x);
	dir.y = (otherPosition.y - getPosition().y) / abs(otherPosition.y - getPosition().y);
	
	return dir;
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

void Enemy::lookForPlayer(Player& player) {
	auto playerDirN = getDirectionOfOtherN(player.getPosition());
	if (getDistance(player.getPosition()) < agroRange) {
		if ((getDirectionOfOther(player.getPosition()).x < 0.f && !faceRight) || (getDirectionOfOther(player.getPosition()).x > 0.f && faceRight)) {
			//player is seen
			//go chase him
			state = Chase;
			velocity.x = speed;
		}
		
		velocity.x = abs(velocity.x) * playerDirN.x;
	}
	else if (state == Chase) {
		state = Idle;
		idleTimer = 0.f;
	}


	if (velocity.x != 0.f) {
		if (velocity.x > 0.f)
			faceRight = true;
		else
			faceRight = false;
	}
}