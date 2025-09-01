#pragma once
#include <SFML/Graphics.hpp>

class Background
{
public:
	Background(sf::Texture* backgroundTexture);

	void Draw(sf::RenderWindow& window) { window.draw(background); }
	void Move(sf::Vector2f offset) { background.move(offset); }
	void Restart();
	void Update(float deltaTime, sf::Vector2f playerVelocity);

	void SetPosition(float x, float y) { background.setPosition(x, y); }
	void SetPosition(sf::Vector2f position) { background.setPosition(position); }
	void SetScale(sf::Vector2f factors) { background.setScale(factors); }


	sf::Vector2f GetPosition() { return background.getPosition(); }
	sf::Vector2u GetSize() { return background.getTexture()->getSize(); }
	sf::Vector2f GetScale() { return background.getScale(); }

public:
	float parlaxStrength = 1.f;

private:
	sf::Sprite background;
};

