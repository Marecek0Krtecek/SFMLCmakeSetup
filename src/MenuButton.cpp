#include "MenuButton.h"

MenuButton::MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor) {
	body.setSize(size);
	body.setPosition(pos);
	body.setOrigin(size / 2.f);
	this->defaultColor = backgroundColor;
}

bool MenuButton::Update(sf::Vector2f cursorPos) {
	body.setFillColor(defaultColor);
	return body.getGlobalBounds().contains(cursorPos);
}

void MenuButton::Hower(sf::Color color) {
	body.setFillColor(color);
}
