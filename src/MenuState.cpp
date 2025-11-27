#include "MenuState.h"
#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window, StateManager& manager) :
	manager(manager),
	window(window),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f())
{
	ResizeView(window, view);

	GameButton = MenuButton(sf::Vector2f(0.f, -200.f), sf::Vector2f(500.f, 100.f), sf::Color::Red);
	EditorButton = MenuButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(500.f, 100.f), sf::Color::Green);
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
		GameButton.Hower();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			manager.changeState<GameState>(window, manager);
		}
	}
	if (EditorButton.Update(cursorPos)) {
		EditorButton.Hower();
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

void MenuState::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}