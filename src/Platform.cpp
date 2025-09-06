#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	if (rand() % 20 == 15)
		canHaveEnemy = true;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	if (rand() % 20 == 15)
		canHaveEnemy = true;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::IntRect& uvRect) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);
	if (rand() % 20 == 15)
		canHaveEnemy = true;

	this->uvRect = uvRect;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::IntRect& uvRect, const std::string& platfomTexture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);
	if (rand() % 20 == 15)
		canHaveEnemy = true;

	this->platformTexture = platfomTexture;
	this->uvRect = uvRect;
}