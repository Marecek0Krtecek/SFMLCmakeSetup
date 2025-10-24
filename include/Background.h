#pragma once
#include <SFML/Graphics.hpp>

class Background
{
public:
	Background(sf::Texture* backgroundTexture);
	Background(sf::Texture* backgroundTexture, sf::Vector2f size, sf::Vector2f position);

	void Draw(sf::RenderWindow& window);
	void Move(sf::Vector2f offset) { background.move(offset); }
	void Restart();
	void Update(float deltaTime, sf::Vector2f playerVelocity);

	void SetPosition(float x, float y) { background.setPosition(x, y); }
	void SetPosition(sf::Vector2f position) { background.setPosition(position); }
	void SetScale(sf::Vector2f factors) { background.setScale(factors); }
	void SetSize(sf::Vector2f size) { background.setSize(size); }


	sf::Vector2f GetPosition() const { return background.getPosition(); }
	sf::Vector2f GetSize() const { return background.getSize(); }
	sf::Vector2f GetScale() const { return background.getScale(); }

public:
	float parlaxStrength = 1.f;

private:
	sf::RectangleShape background;
};

