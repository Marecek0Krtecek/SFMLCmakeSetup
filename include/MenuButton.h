#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MenuButton
{
public:
	MenuButton() = default;
	MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Color backgroundColor);
	MenuButton(sf::Vector2f pos, sf::Vector2f size, sf::Texture* texture);
	~MenuButton() = default;

	bool Update(sf::Vector2f cursorPos);

	void Hower(sf::Color color = sf::Color(50, 50, 50, 127));

	void Draw(sf::RenderWindow& window) const { window.draw(body); window.draw(text); }

private:
	sf::RectangleShape body;

	sf::Font font;
	sf::Text text;

	sf::Color defaultColor;
};