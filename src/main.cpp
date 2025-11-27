#include "MenuState.h"

using json = nlohmann::json;

int main() 
{
#pragma region SetupStuf

	sf::RenderWindow window(sf::VideoMode(1280, 720), "myGame", sf::Style::Default);

	window.setFramerateLimit(60);

	ImGui::SFML::Init(window);

	float deltaTime = 0;
	sf::Clock clock;

	StateManager stateManager;
	
	stateManager.changeState<MenuState>(window, stateManager);
	//stateManager.changeState<GameState>(window, stateManager);
	//stateManager.changeState<EditorState>(window, stateManager);
	
#pragma endregion

#pragma region ImGui SetUp

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 1.5f;

#pragma endregion

	while (window.isOpen()) {

		deltaTime = clock.restart().asSeconds();

#pragma region poll events

		sf::Event ev;
		while (window.pollEvent(ev)) {
			ImGui::SFML::ProcessEvent(window, ev);

			if (ev.type == sf::Event::Closed) {
				window.close();
			}

			stateManager.handleEvent(ev, window);
		}

#pragma endregion

#pragma region ImGui Update

		ImGui::SFML::Update(window, clock.restart()); 

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);

#pragma endregion

		stateManager.update(deltaTime);

		window.clear();

		stateManager.render(window);

		ImGui::SFML::Render(window);

		window.display();

	}

	ImGui::SFML::Shutdown();
	return 0;

}