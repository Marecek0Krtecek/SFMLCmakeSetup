#include "Checkpoint.h"

Checkpoint::Checkpoint(sf::Vector2f position, const std::string& name) {
	point.setRadius(15.f);
	point.setPosition(position.x - point.getRadius(), position.y - point.getRadius());
	point.setFillColor(sf::Color::Green);

	this->name = name;

	if (name == "spawn") { 
		point.setOutlineColor(sf::Color::Magenta); 
		point.setOutlineThickness(3.f);
	}
}