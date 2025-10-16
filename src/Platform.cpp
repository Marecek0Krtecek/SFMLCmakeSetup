#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);

	this->uvRect = uvRect;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect, const std::string& platfomTexture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);

	this->platformTexture = platfomTexture;
	this->uvRect = uvRect;
}