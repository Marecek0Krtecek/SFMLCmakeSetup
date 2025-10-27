#include "Background.h"

Background::Background(sf::Texture* backgroundTexture) {
	//backgroundTexture->setRepeated(true);
	background.setTexture(backgroundTexture);
	background.setSize(sf::Vector2f(backgroundTexture->getSize().x * 15.f, backgroundTexture->getSize().y * 15.f));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(sf::Vector2f(0.f, 0.f));
}

Background::Background(sf::Texture* backgroundTexture, sf::Vector2f size, float parllax, const std::string& texturePath) {
	background.setTexture(backgroundTexture);
	background.setSize(size);
	background.setOrigin(size / 2.f);

	parlaxStrength = parllax;
	this->texturePath = texturePath;
}

void Background::Draw(sf::RenderWindow& window) {
	const auto& view = window.getView();
	sf::Vector2f parllaxOffset = -view.getCenter() * parlaxStrength;


	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			int posX = x + int((view.getCenter().x - parllaxOffset.x) / GetSize().x);
			int posY = y + int((view.getCenter().y - parllaxOffset.y) / GetSize().y);

			sf::Vector2f drawPos(posX * GetSize().x + parllaxOffset.x, posY * GetSize().y + parllaxOffset.y);

			background.setPosition(drawPos);
			
			window.draw(background);
		}
	}

}

//void Background::Draw(sf::RenderWindow& window) {
//
//	const auto& view = window.getView();
//	sf::Vector2f parllaxOffset = view.getCenter() * parlaxStrength;
//
//	background.setSize(view.getSize() * 3.f);
//
//	sf::IntRect texRect(
//		int(parllaxOffset.x) % int(view.getSize().x),
//		int(parllaxOffset.y) % int(view.getSize().y),
//		int(background.getSize().x),
//		int(background.getSize().y)
//	);
//
//	background.setTextureRect(texRect);
//
//	background.setPosition(view.getCenter() - background.getSize() / 2.f);
//
//	window.draw(background);
//}

void Background::Restart() {
	background.setPosition(sf::Vector2f(0.f, 0.f));
}

void Background::Update(float deltaTime, sf::Vector2f playerVelocity) {
	background.move(-playerVelocity * parlaxStrength * deltaTime);
}