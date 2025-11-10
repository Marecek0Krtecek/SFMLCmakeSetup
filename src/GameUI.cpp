#include "GameUI.h"

GameUI::GameUI(const sf::View& view, const Player& player) :
	view(view),
	player(player)
{
	shapes["HPBar"] = sf::RectangleShape(sf::Vector2f(50.f, 5.f));
	shapes["HPBar"].setFillColor(sf::Color(100, 0, 0));
	shapes["HPBar"].setOrigin(shapes["HPBar"].getSize() / 2.f);
	shapes["HPBar"].setPosition(view.getCenter().x, view.getCenter().y - 40.f);
	shapes["HPBar"].setOutlineColor(sf::Color(75, 0, 0));
	shapes["HPBar"].setOutlineThickness(3.f);

	shapes["HPShow"] = sf::RectangleShape(shapes["HPBar"].getSize());
	shapes["HPShow"].setFillColor(sf::Color(255, 0, 0));
	shapes["HPShow"].setPosition(shapes["HPBar"].getPosition().x - (shapes["HPBar"].getSize().x / 2.f), shapes["HPBar"].getPosition().y - (shapes["HPBar"].getSize().y / 2.f));
}

void GameUI::update(float deltaTime) {
	shapes["HPBar"].setPosition(view.getCenter().x, view.getCenter().y - 40.f);

	shapes["HPShow"].setPosition(shapes["HPBar"].getPosition().x - (shapes["HPBar"].getSize().x / 2.f), shapes["HPBar"].getPosition().y - (shapes["HPBar"].getSize().y / 2.f));
	shapes["HPShow"].setSize(sf::Vector2f(shapes["HPBar"].getSize().x * (player.health / player.GetMaxHealth()), shapes["HPBar"].getSize().y));
}

void GameUI::Draw(sf::RenderWindow& window) {
	for (auto& [name, shape] : shapes) {
		window.draw(shape);
	}
}