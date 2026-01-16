#include "Platform.h"

Platform::Platform(sf::Vector2f size, sf::Vector2f position) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);

	this->top = GetPosition().y - GetCollider().GetHalfSize().y;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);

	this->top = GetPosition().y - GetCollider().GetHalfSize().y;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);

	this->uvRect = uvRect;

	this->top = GetPosition().y - GetCollider().GetHalfSize().y;
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, const sf::IntRect& uvRect, const std::string& platfomTexture) {
	body.setSize(size);
	body.setOrigin(size / 2.f);
	body.setPosition(position);
	body.setTexture(texture);
	body.setTextureRect(uvRect);

	this->platformTexture = platfomTexture;
	this->uvRect = uvRect;

	this->top = GetPosition().y - GetCollider().GetHalfSize().y;
}