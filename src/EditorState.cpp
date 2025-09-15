#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow& window) :
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT))
{
	ResizeView(window, view);

	platforms.reserve(10);

	textures.loadTexture(platformTexture);

	tileManager.loadFromFile(RESOURCES_PATH "config.json");

	tileNames.reserve(tileManager.getAllTiles().size());
	strTileNames.reserve(tileManager.getAllTiles().size());

	for (const auto& [name, def] : tileManager.getAllTiles()) {
		strTileNames.push_back(name);
	}

	for (const auto& name : strTileNames) {
		tileNames.push_back(name.c_str());
	}
}

void EditorState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	
	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
		if (event.key.code == sf::Keyboard::Q) view.zoom(zoomFactor);
		if (event.key.code == sf::Keyboard::E) view.zoom(1.f / zoomFactor);

		break;
	case sf::Event::Resized:
		ResizeView(window, view);
		break;
	case sf::Event::MouseWheelScrolled:
		break;
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Left && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
			selectPos = window.mapPixelToCoords(pixelPos, view);
			selectPos = snapToGridFunc(selectPos, gridSize, snapToGrid);
		}
		break;
	}

}

void EditorState::update(float deltaTime) {
#pragma region View moving

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) view.move(0.f, -panSpeed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) view.move(0.f, panSpeed * deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) view.move(-panSpeed * deltaTime, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) view.move(panSpeed * deltaTime, 0.f);

#pragma endregion

#pragma region ImGui

#pragma region File

	ImGui::Begin("File");

	if (ImGui::Button("Save Level")) {
		saveWindow = !saveWindow;
	}
	
	if(saveWindow){
		static std::string saveDirectory = "";
		static bool isChosen = false;

		ImGui::Begin("Save To File");
		
		ImGui::InputText("File Name To Save To", &saveDirectory);

		if (ImGui::Button("Choose")) {
			isChosen = true;
		}

		ImGui::End();

		if (isChosen) {
			std::ofstream save(RESOURCES_PATH + saveDirectory);
			save << Serializer::savePlatforms(platforms).dump(4);

			save.close();

			saveWindow = false;
			isChosen = false;
		}
	}

	if (ImGui::Button("Load Level")) {
		loadWindow = !loadWindow;
	}

	if (loadWindow) {
		static std::string loadDirectory = "";
		static bool isChosen = false;
		
		ImGui::Begin("Load From File");

		ImGui::InputText("File Name To Load From", &loadDirectory);

		if (ImGui::Button("Choose")) {
			isChosen = true;
		}

		ImGui::End();

		if (isChosen) {
			std::ifstream file(RESOURCES_PATH + loadDirectory);
			if (file.is_open()) {
				nlohmann::json j;
				
				file >> j;
				
				platforms.erase(platforms.begin(), platforms.end());
				Serializer::loadPlatforms(j, platforms, textures, tileManager);

				file.close();

				loadWindow = false;
				isChosen = false;
			}
		}
	}

	ImGui::End();

#pragma endregion

	ImGui::Begin("Editor Window");

	if (ImGui::Button("Platform Creation")) {
		platformWindow = !platformWindow;
	}
	if (ImGui::Button("Platform Editing")) {
		platformEditWindow = !platformEditWindow;
	}
	if (ImGui::Button("Grid Settings")) {
		gridSettingWindow = !gridSettingWindow;
	}

	ImGui::End();

#pragma region Platforms

	if (platformWindow) {
		ImGui::Begin("Platforms");
		static float* floatArr[] = { &selectPos.x, &selectPos.y, &selectSize.x, &selectSize.y };
		if (ImGui::InputFloat4("X, Y, W, H", *floatArr, "%.1f")) {
			selectPos = snapToGridFunc(selectPos, gridSize, snapToGrid);
		}

		ImGui::Combo("Texture", &currentItem, tileNames.data(), (int)tileNames.size());
		auto* def = tileManager.getTile(strTileNames[currentItem]);
		if (def) {
			auto& atlasTexture = textures.get(def->textureAdress);
			sf::Sprite texturePreview(atlasTexture, def->rect);

			static float scale = 5.f;
			ImGui::SliderFloat("Set Scale", &scale, 1.f, 10.f, "%.1f");

			texturePreview.setScale(scale, scale);
			ImGui::Image(texturePreview);

			ImGui::Checkbox("Snap To Grid", &snapToGrid);

			if (ImGui::Button("Add Platform")) {
				platforms.push_back(Platform(selectSize, selectPos, &atlasTexture, def->rect, def->name));
				selectPos = {};
			}
		}

		if (ImGui::Button("Clear Choices")) {
			selectSize = {};
			selectPos = {};
			currentItem = 0;
		}
		ImGui::End();
	}

	if (platformEditWindow) {
		ImGui::Begin("Edit Platforms");

		static int selectedIndex = -1;
		if (selectedIndex < 0) {
			for (int i = 0; i < platforms.size(); i++) {
				std::string label = "Platform " + std::to_string(i);
				if (ImGui::Selectable(label.c_str(), selectedIndex == i)) {
					selectedIndex = i;
				}
			}
		}
		else {
			auto& platform = platforms[selectedIndex];
			if (ImGui::Button("Exit")) {
				selectedIndex = -1;
			}
			
			sf::Vector2f pos = platform.GetPosition();
			sf::Vector2f size = platform.GetSize();

			if (ImGui::InputFloat2("X, Y", &pos.x, "%.1f")) {
				platform.SetPosition(snapToGridFunc(pos, gridSize, snapToGrid));
			}
			if (ImGui::InputFloat2("W, H", &size.x, "%.1f")) {
				platform.SetSize(size);
			}

			if (ImGui::Combo("Texture", &currentItem, tileNames.data(), (int)tileNames.size())) {
				platform.SetTextureRect(tileManager.getTile(strTileNames[currentItem])->rect);
			}

			if (ImGui::Button("Delete Platform")) {
				platforms.erase(platforms.begin() + selectedIndex);
				selectedIndex = -1;
			}
		}

		ImGui::End();

	}
#pragma endregion

#pragma region Grid Settings

	if (gridSettingWindow) {
		ImGui::Begin("Grid Settings");

		ImGui::Checkbox("Snap To Grid", &snapToGrid);
		ImGui::SliderFloat("Grid Size", &gridSize, 8.f, 128.f, "%.1f");

		ImGui::End();
	}

#pragma endregion


#pragma endregion

}

void EditorState::render(sf::RenderWindow& window) {
	
	window.setView(view);

	drawGrid(window, gridSize);

	for (auto& platform : platforms) {
		platform.Draw(window);
	}

}

void EditorState::ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

sf::Vector2f EditorState::snapToGridFunc(const sf::Vector2f& pos, const float& gridSize, bool enabled) {
	if (!enabled) return pos;
	return sf::Vector2f(
		std::round(pos.x / gridSize) * gridSize,
		std::round(pos.y / gridSize) * gridSize
	);
}

void EditorState::drawGrid(sf::RenderWindow& window, const float& gridSize) {
	const auto& view = window.getView();
	const auto& center = view.getCenter();
	const auto& size = view.getSize();

	float left = center.x - size.x / 2.f;
	float right = center.x + size.x / 2.f;
	float top = center.y - size.y / 2.f;
	float bottom = center.y + size.y / 2.f;

	sf::VertexArray lines(sf::Lines);

	//vertikálne èiary
	for (float x = std::floor(left / gridSize) * gridSize; x < right; x += gridSize) {
		lines.append(sf::Vertex(sf::Vector2f(x, top), sf::Color(80, 80, 80)));
		lines.append(sf::Vertex(sf::Vector2f(x, bottom), sf::Color(80, 80, 80)));
	}

	//horizontálne èiary
	for (float y = std::floor(top / gridSize) * gridSize; y < bottom; y += gridSize) {
		lines.append(sf::Vertex(sf::Vector2f(left, y), sf::Color(80, 80, 80)));
		lines.append(sf::Vertex(sf::Vector2f(right, y), sf::Color(80, 80, 80)));
	}
	
	window.draw(lines);
}