#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow& window, StateManager& manager) :
	stateManager(manager),
	window(window)
{
	const auto& view = window.getView();
	buttons["ResumeGame"] = MenuButton(sf::Vector2f(view.getCenter().x, view.getCenter().y - 150.f - 200.f), sf::Vector2f(300.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052, 0, 1052, 320));
	buttons["ChangeEditor"] = MenuButton(sf::Vector2f(view.getCenter().x, view.getCenter().y - 200.f), sf::Vector2f(300.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052 * 2, 0, 1052, 320));
	buttons["ExitGame"] = MenuButton(sf::Vector2f(view.getCenter().x, view.getCenter().y + 150.f - 200.f), sf::Vector2f(300.f, 100.f), &textures.get("menu_design/boxes_sharp_1.png"), sf::IntRect(1052 * 4, 0, 1052, 320));

	background.setPosition(view.getCenter());
	background.setSize(view.getSize());
	background.setOrigin(background.getSize() / 2.f);
	background.setFillColor(sf::Color(128, 128, 128, 128));
}

void PauseState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape) stateManager.popState();
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left) isButtonPressed = true;
		break;
	default:
		break;
	}
}

void PauseState::update(float deltaTime) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f cursorPos = window.mapPixelToCoords(mousePos, window.getView());

	if (buttons["ResumeGame"].Update(cursorPos)) {
		buttons["ResumeGame"].Hower(sf::IntRect(sf::Vector2i(buttons["ResumeGame"].GetUvRect().left, buttons["ResumeGame"].GetUvRect().height), buttons["ResumeGame"].GetUvRect().getSize()));
		if (isButtonPressed) {
			isButtonPressed = false;
			stateManager.popState();
			return;
		}
	}

	if (buttons["ChangeEditor"].Update(cursorPos)) {
		buttons["ChangeEditor"].Hower(sf::IntRect(sf::Vector2i(buttons["ChangeEditor"].GetUvRect().left, buttons["ChangeEditor"].GetUvRect().height), buttons["ChangeEditor"].GetUvRect().getSize()));
		if (isButtonPressed) {
			isButtonPressed = false;
			stateManager.changeState<EditorState>(window, stateManager);
			return;
		}
	}

	if (buttons["ExitGame"].Update(cursorPos)) {
		buttons["ExitGame"].Hower(sf::IntRect(sf::Vector2i(buttons["ExitGame"].GetUvRect().left, buttons["ExitGame"].GetUvRect().height), buttons["ExitGame"].GetUvRect().getSize()));
		if (isButtonPressed) {
			isButtonPressed = false;
			stateManager.changeState<MenuState>(window, stateManager);
			return;
		}
	}

	isButtonPressed = false;
}

void PauseState::render(sf::RenderWindow& window) {
	window.draw(background);

	for (auto& [name, button] : buttons) {
		button.Draw(window);
	}
}

void PauseState::ResizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}