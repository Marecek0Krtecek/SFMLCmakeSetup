#include "MenuButton.h"
#include "MenuButton.h"
#include "MenuButton.h"

MenuButton::MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor) {
	body.setSize(size);
	body.setPosition(pos);
	body.setOrigin(size / 2.f);

	this->defaultColor = backgroundColor;
}

MenuButton::MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Texture* texture, sf::IntRect textureRect) {
	body.setSize(size);
	body.setPosition(pos);
	body.setOrigin(size / 2.f);

	body.setTexture(texture);

	this->uvRect = textureRect;

}

bool MenuButton::Update(sf::Vector2f cursorPos) {
	if (defaultColor == sf::Color::Transparent) body.setTextureRect(uvRect);
	else body.setFillColor(defaultColor);
	return body.getGlobalBounds().contains(cursorPos);
}

void MenuButton::Hower(sf::Color color) {
	body.setFillColor(color);
}

void MenuButton::Hower(sf::IntRect hoverTextureRect) {
	body.setTextureRect(hoverTextureRect);
}
