#include "Background.h"

Background::Background(sf::Texture* backgroundTexture) {
	background.setPosition(sf::Vector2f(0.f, 0.f));
	background.setTexture(*backgroundTexture);
	background.setOrigin(backgroundTexture->getSize().x / 2.f, backgroundTexture->getSize().y / 2.f);
}

void Background::Restart() {
	background.setPosition(sf::Vector2f(0.f, 0.f));
}

void Background::Update(float deltaTime, sf::Vector2f playerVelocity) {
	Move(-playerVelocity * parlaxStrength * deltaTime);
}