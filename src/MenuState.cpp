#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window, StateManager& manager) :
	manager(manager),
	window(window),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f())
{
	ResizeView(window, view);

	GameButton = MenuButton(sf::Vector2f(0.f, -150.f), sf::Vector2f(500.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(0, 0, 1052, 320));
	EditorButton = MenuButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(500.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052 * 2, 0, 1052, 320));

	background.setSize(sf::Vector2f(843.f, 596.f));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(0.f, 0.f);
	background.setTexture(&textures.get("menu_design/menu_background.png"));
}

void MenuState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::Resized:
		ResizeView(window, view);
		break;
	}
}

void MenuState::update(float deltaTime) {
	mousePos = sf::Mouse::getPosition(window);
	cursorPos = window.mapPixelToCoords(mousePos, view);

	if (GameButton.Update(cursorPos)) {
		GameButton.Hower(sf::IntRect(sf::Vector2i(GameButton.GetUvRect().left, GameButton.GetUvRect().height), GameButton.GetUvRect().getSize()));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			manager.changeState<GameState>(window, manager);
		}
	}
	if (EditorButton.Update(cursorPos)) {
		EditorButton.Hower(sf::IntRect(sf::Vector2i(EditorButton.GetUvRect().left, EditorButton.GetUvRect().height), EditorButton.GetUvRect().getSize()));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			manager.changeState<EditorState>(window, manager);
		}
	}

}

void MenuState::render(sf::RenderWindow& window) {
	window.setView(view);

	window.draw(background);

	GameButton.Draw(window);
	EditorButton.Draw(window);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuState::ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}