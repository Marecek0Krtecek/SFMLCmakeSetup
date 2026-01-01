#include "GameUI.h"

GameUI::GameUI(const sf::View& view, const Player& player) :
	view(view),
	player(player)
{
	
}

void GameUI::update(float deltaTime) {

}

void GameUI::Draw(sf::RenderWindow& window) {
	for (auto& [name, shape] : shapes) {
		window.draw(shape);
	}
}