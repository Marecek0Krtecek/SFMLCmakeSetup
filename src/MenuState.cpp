#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow& window, StateManager& manager) :
	manager(manager),
	window(window),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f())
{
	buttons["GameButton"] = MenuButton(sf::Vector2f(0.f, -150.f), sf::Vector2f(500.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(0, 0, 1052, 320));
	buttons["EditorButton"] = MenuButton(sf::Vector2f(0.f, 0.f), sf::Vector2f(500.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052 * 2, 0, 1052, 320));
	buttons["EndButton"] = MenuButton(sf::Vector2f(0.f, 150.f), sf::Vector2f(500.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052 * 4, 0, 1052, 320));

	background.setSize(backgroundSize);
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(0.f, 0.f);
	background.setTexture(&textures.get("menu_design/menu_background.png"));
	defRect = background.getTextureRect();

	textures.get("menu_design/menu_background.png").setRepeated(true);
	
	ResizeView(window, view);

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

	if (buttons["GameButton"].Update(cursorPos)) {
		buttons["GameButton"].Hower(sf::IntRect(sf::Vector2i(buttons["GameButton"].GetUvRect().left, buttons["GameButton"].GetUvRect().height), buttons["GameButton"].GetUvRect().getSize()));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			manager.changeState<GameState>(window, manager);
			return;
		}
	}
	if (buttons["EditorButton"].Update(cursorPos)) {
		buttons["EditorButton"].Hower(sf::IntRect(sf::Vector2i(buttons["EditorButton"].GetUvRect().left, buttons["EditorButton"].GetUvRect().height), buttons["EditorButton"].GetUvRect().getSize()));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			manager.changeState<EditorState>(window, manager);
			return;
		}
	}
	if (buttons["EndButton"].Update(cursorPos)) {
		buttons["EndButton"].Hower(sf::IntRect(sf::Vector2i(buttons["EndButton"].GetUvRect().left, buttons["EndButton"].GetUvRect().height), buttons["EndButton"].GetUvRect().getSize()));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			window.close();
			return;
		}
	}

}

void MenuState::render(sf::RenderWindow& window) {
	window.setView(view);

	window.draw(background);

	for (const auto& [name, button] : buttons) {
		button.Draw(window);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuState::ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);

	if (view.getSize().x > backgroundSize.x) {
		background.setSize(sf::Vector2f(view.getSize().x, background.getSize().y));
		background.setOrigin(background.getSize() / 2.f);

		background.setTextureRect(sf::IntRect(
			-abs(view.getSize().x / 2.f - backgroundSize.x / 2.f),
			0,
			abs(view.getSize().x / 2.f - backgroundSize.x / 2.f) + backgroundSize.x + abs(view.getSize().x / 2.f - backgroundSize.x / 2.f),
			background.getSize().y
		));
	}
	else {
		background.setSize(backgroundSize);
		background.setOrigin(background.getSize() / 2.f);
		background.setTextureRect(defRect);
	}

}