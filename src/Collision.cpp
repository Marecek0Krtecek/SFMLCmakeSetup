#include "Collision.h"

Collision::Collision(sf::RectangleShape& body) :
	body(body)
{

}

bool Collision::CheckCollision(Collision& other, sf::Vector2f& direction, float weight) {
	
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f) {
		weight = std::min(std::max(weight, 0.f), 1.f);

		if (intersectX > intersectY) {
			if (deltaX > 0.f) {
				Move(intersectX * (1.f - weight), 0.f);
				other.Move(-intersectX * weight, 0.f);

				direction.x = 1.f;		//collision on right
				direction.y = 0.f;
			}
			else {
				Move(-intersectX * (1.f - weight), 0.f);
				other.Move(intersectX * weight, 0.f);

				direction.x = -1.f;		//colision on left
				direction.y = 0.f;
			}
		}
		else {
			if (deltaY > 0.f) {
				Move(0.f,intersectY * (1.f - weight));
				other.Move(0.f,-intersectY * weight);

				direction.x = 0.f;
				direction.y = 1.f;		//collision on bottom
			}
			else {
				Move(0.f,-intersectY * (1.f - weight));
				other.Move(0.f, intersectY * weight);

				direction.x = 0.f;
				direction.y = -1.f;		//colision on top
			}
		}
		
		return true;
	}

	return false;
}