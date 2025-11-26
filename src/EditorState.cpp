#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow& window, StateManager& manager) :
	stateManager(manager),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT))
{
	ResizeView(window, view);

	platforms.reserve(100);
	enemySpawnPoints.reserve(100);
	backgrounds.reserve(5);
	checkpoints.reserve(10);
	
	//textures.loadTexture(platformTexture);

	tileManager.loadFromFile(RESOURCES_PATH "config.json");
	enemyManager.loadFromFile(RESOURCES_PATH "config.json");

	tileNames.reserve(tileManager.getAllTiles().size());
	strTileNames.reserve(tileManager.getAllTiles().size());

	for (const auto& [name, def] : tileManager.getAllTiles()) {
		strTileNames.push_back(name);
		tileNames.push_back(name.c_str());
	}

	enemyTxNames.reserve(enemyManager.getAllEnemies().size());
	strEnemyTxNames.reserve(enemyManager.getAllEnemies().size());

	for (const auto& [name, def] : enemyManager.getAllEnemies()) {
		strEnemyTxNames.push_back(name);
		enemyTxNames.push_back(name.c_str());
	}
}

void EditorState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	
	switch (event.type)
	{
	case sf::Event::KeyPressed:

		//if (event.key.code == sf::Keyboard::Escape) window.close();
		if (event.key.code == sf::Keyboard::Q) view.zoom(zoomFactor);
		if (event.key.control && event.key.code == sf::Keyboard::E);
		else if (event.key.code == sf::Keyboard::E) view.zoom(1.f / zoomFactor);
		if (event.key.control && event.key.shift && event.key.code == sf::Keyboard::D) duplicateEnemy(eSelectedIndex);
		if (event.key.control && event.key.code == sf::Keyboard::D) duplicatePlatform(pSelectedIndex);
		if (event.key.control && event.key.code == sf::Keyboard::X) {
			deletePlatform(pSelectedIndex);
			deleteEnemy(eSelectedIndex);
			deleteBackground(bSelectedIndex);
			deleteCheckpoint(cSelectedIndex);
		}
		if (event.key.control && event.key.code == sf::Keyboard::Z) undo();
		if (event.key.control && event.key.code == sf::Keyboard::Y) redo();

		if (event.key.shift && event.key.control && event.key.code == sf::Keyboard::S) saveAs();
		else if (event.key.control && event.key.code == sf::Keyboard::S) {
			if (currentFilePath == "") {
				saveAs();
			}
			else {
				save();
			}
		}

		if (event.key.control && event.key.code == sf::Keyboard::O) loadLevel();
		if (event.key.control && event.key.code == sf::Keyboard::N) {
			if (isSaved) {
				clearLevel();

				platforms.reserve(platforms.size() + 100);
				enemySpawnPoints.reserve(enemySpawnPoints.size() + 100);
				backgrounds.reserve(backgrounds.size() + 5);
				checkpoints.reserve(checkpoints.size() + 10);
			}
			else {
				newLevelIsNotSaved = true;
			}
		}

		// state change
		if (event.key.code == sf::Keyboard::F5) stateManager.changeState<GameState>(window, stateManager);

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

			if (pSelectedIndex >= 0) {
				movePlatform(pSelectedIndex, platforms[pSelectedIndex].GetPosition(), selectPos);
			}
			if (eSelectedIndex >= 0) {
				moveEnemy(eSelectedIndex, enemySpawnPoints[eSelectedIndex].GetPosition(), selectPos);
			}
			if (cSelectedIndex >= 0) {
				moveCheckpoint(checkpoints[cSelectedIndex], selectPos);
			}

		}
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);

			int i = 0;
			for (const auto& platform : platforms) {
				if (platform.GetGlobalBounds().contains(worldPos)) {
					pSelectedIndex = i;
					platformEditWindow = true;
					break;
				}
				i++;
			}

			i = 0;
			for (const auto& enemySP : enemySpawnPoints) {
				if (enemySP.GetGlobalBounds().contains(worldPos)) {
					eSelectedIndex = i;
					enemyEditWindow = true;
					break;
				}
				i++;
			}

			i = 0;
			for (const auto& checkpoint : checkpoints) {
				if (checkpoint.GetGlobalBounds().contains(worldPos)) {
					cSelectedIndex = i;
					playerCheckpointsWindow = true;
					break;
				}
				i++;
			}
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

	std::string info = "Selected File : \t" + currentFilePath;
	ImGui::Text(info.c_str());

	if (ImGui::Button("New Level")) {
		// TODO: vypr·zdniù platformy, spawnpointy, atÔ.

		if (isSaved) {
			clearLevel();

			platforms.reserve(platforms.size() + 100);
			enemySpawnPoints.reserve(enemySpawnPoints.size() + 100);
			backgrounds.reserve(backgrounds.size() + 10);
		}
		else{
			newLevelIsNotSaved = true;
		}

	}

	if (newLevelIsNotSaved) {

		ImGui::Begin("Are You Sure?");

		ImGui::Text("The Level Is Not Saved,\ndo you wish to clear the level?");
		if (ImGui::Button("Yes")) {
			clearLevel();

			platforms.reserve(platforms.size() + 100);
			enemySpawnPoints.reserve(enemySpawnPoints.size() + 100);
			newLevelIsNotSaved = false;
		}

		if (ImGui::Button("Save")) {
			if (currentFilePath != std::string()) {
				save();
			}
			else {
				saveAs();
			}
			newLevelIsNotSaved = false;
		}

		if (ImGui::Button("Cancel")) {
			newLevelIsNotSaved = false;
		}

		ImGui::End();
	}

	if (ImGui::Button("Load Level")) {
		// TODO: zatiaæ natvrdo "level.json", neskÙr prid·me file dialog
		loadLevel();
	}

	if (ImGui::Button("Save Level")) {
		// TODO: uloûiù na posledn˙ zn·mu cestu
		if (currentFilePath != std::string()) {
			save();
		}
		else {
			saveAs();
		}

	}

	if (ImGui::Button("Save Level As...")) {
		// TODO: uloûiù na nov˙ cestu (zatÌm staËÌ hardcode)
		saveAs();
	}

	if (ImGui::Button("Save Level old")) {
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
			nlohmann::json j;
			j["platform"] = Serializer::savePlatforms(platforms);
			j["enemy"] = Serializer::saveEnemySpawnPoints(enemySpawnPoints);
			save << j.dump(4);

			save.close();

			saveWindow = false;
			isChosen = false;
			isSaved = true;
		}
	}

	if (ImGui::Button("Load Level old")) {
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


				enemySpawnPoints.erase(enemySpawnPoints.begin(), enemySpawnPoints.end());
				Serializer::loadEnemySpawnPoints(j, enemySpawnPoints);

				platforms.reserve(platforms.size() + 100);
				enemySpawnPoints.reserve(enemySpawnPoints.size() + 100);

				file.close();

				loadWindow = false;
				isChosen = false;

				isSaved = true;
			}
		}
	}

	ImGui::End();

	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

			currentFilePath = fileFinding(filePathName);

			load();
		}

		ImGuiFileDialog::Instance()->Close();
	}

	if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey")) {
		if (ImGuiFileDialog::Instance()->IsOk()) {
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

			currentFilePath = fileFinding(filePathName);

			save();
		}

		ImGuiFileDialog::Instance()->Close();
	}

#pragma endregion

#pragma region WindowManagment

	ImGui::Begin("Editor Window");

	if (ImGui::Button("Platform Creation")) {
		platformWindow = !platformWindow;
		currentItem = 0;
	}
	if (ImGui::Button("Platform Editing")) {
		platformEditWindow = !platformEditWindow;
		currentItem = 0;
	}
	if (ImGui::Button("Enemy Spawn Poind Creation")) {
		enemyWindow = !enemyWindow;
		currentItem = 0;
	}
	if (ImGui::Button("Enemy SP Editing")) {
		enemyEditWindow = !enemyEditWindow;
		currentItem = 0;
	}
	if (ImGui::Button("Grid Settings")) {
		gridSettingWindow = !gridSettingWindow;
	}
	if (ImGui::Button("Background")) {
		backgroundWindow = !backgroundWindow;
	}
	if (ImGui::Button("Player Checkpoints")) {
		playerCheckpointsWindow = !playerCheckpointsWindow;
	}

	if (!platformEditWindow) pSelectedIndex = -1;
	if (!enemyEditWindow) eSelectedIndex = -1;
	if (!backgroundWindow) bSelectedIndex = -1;
	if (!playerCheckpointsWindow) cSelectedIndex = -1;

	ImGui::End();

#pragma endregion

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

			if (ImGui::Button("Add Platform") || ImGui::IsKeyPressed(ImGuiKey_P)) {
				addPlatform(Platform(selectSize, selectPos, &atlasTexture, def->rect, def->name));
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

		if (pSelectedIndex < 0 || platforms.size() == 0) {
			for (int i = 0; i < platforms.size(); i++) {
				std::string label = "Platform " + std::to_string(i);
				if (ImGui::Selectable(label.c_str(), pSelectedIndex == i)) {
					pSelectedIndex = i;
				}
			}
		}
		else {
			if (pSelectedIndex >= platforms.size())
				pSelectedIndex = platforms.size() - 1;

			auto& platform = platforms[pSelectedIndex];
			if (ImGui::Button("Exit")) {
				pSelectedIndex = -1;
			}
			
			sf::Vector2f pos = platform.GetPosition();
			sf::Vector2f size = platform.GetSize();

			if (ImGui::Button("Duplicate")) {
				duplicatePlatform(pSelectedIndex);
			}

			if (ImGui::InputFloat2("X, Y", &pos.x, "%.1f")) {
				pos = snapToGridFunc(pos, gridSize, snapToGrid);
				if(pos != platform.GetPosition())
					movePlatform(pSelectedIndex, platform.GetPosition(), pos);
			}

			if (ImGui::InputFloat2("W, H", &size.x, "%.1f")) {
				if (size != platform.GetSize())
					resizePlatform(pSelectedIndex, platform.GetSize(), size);
			}

			if (strTileNames[currentItem] != platform.GetTexture()) {
				for (int i = 0; i < strTileNames.size(); i++) {
					if (strTileNames[i] == platform.GetTexture()) {
						currentItem = i;
						break;
					}
				}
			}


			if (ImGui::Combo("Texture", &currentItem, tileNames.data(), (int)tileNames.size())) {
					changePlatformTile(pSelectedIndex, platform.GetTexture(), strTileNames[currentItem]);
			}

			if (ImGui::Button("Delete Platform")) {
				deletePlatform(pSelectedIndex);
			}
		}

		ImGui::End();

	}
#pragma endregion

#pragma region Grid Settings

	if (gridSettingWindow) {
		ImGui::Begin("Grid Settings");

		ImGui::Checkbox("Snap To Grid", &snapToGrid);
		if (ImGui::SliderFloat("Grid Size", &gridSize, 8.f, 128.f, "%.1f")) {
			for (auto& platform : platforms) {
				platform.SetPosition(snapToGridFunc(platform.GetPosition(), gridSize, snapToGrid));
			}
		}

		ImGui::End();
	}

#pragma endregion

#pragma region Help Window

	if (ImGui::IsKeyPressed(ImGuiKey_F1)) {
		showHelpWindow = !showHelpWindow;
	}

	if (showHelpWindow) {
		ImGui::Begin("Help");

		ImGui::Text("Ctrl + S: Ulozit level");
		ImGui::Text("Ctrl + Shift + S: Ulozit level ako");
		ImGui::Text("Ctrl + O: Otvorit level");
		ImGui::Text("Ctrl + N: Novy level");
		ImGui::Text("P: Pridat platformu");
		ImGui::Text("Ctrl + D: Duplikovat platformu");
		ImGui::Separator();
		ImGui::Text("Ctrl + X: Zmazat oznacenu platformu\n alebo spawn point");
		ImGui::Separator();
		ImGui::Text("Ctrl + E: Pridat nepriatela");
		ImGui::Text("Ctrl + Shift + D: Duplikovat spawn point");
		ImGui::Separator();
		ImGui::Text("Ctrl + Z: Undo");
		ImGui::Text("Ctrl + Y: Redo");
		ImGui::Separator(); 
		ImGui::Text("Q: Zoom -");
		ImGui::Text("E: Zoom +");
		ImGui::Separator(); 
		ImGui::Text("F1: Zobrazit tuto napovedu");
		ImGui::Text("F5: Zmenit mod");

		ImGui::End();
	}

#pragma endregion

#pragma region Enemies
	
	if (enemyWindow) {
		ImGui::Begin("Enemy");

		if (ImGui::InputFloat2("X, Y", &selectPos.x, "%.1f")) {
			selectPos = snapToGridFunc(selectPos, gridSize, snapToGrid);
		}

		ImGui::Combo("Texture", &currentItem, enemyTxNames.data(), enemyTxNames.size());
		auto* def = enemyManager.getEnemy(strEnemyTxNames[currentItem]);

		if (def) {
			auto& atlasTexture = textures.get(def->textureAdress);
			sf::Sprite texturePreview(atlasTexture, def->rect);

			static float scale = 5.f;
			ImGui::SliderFloat("Set Scale", &scale, 1.f, 10.f, "%.1f");

			texturePreview.setScale(scale, scale);
			ImGui::Image(texturePreview);

			ImGui::Checkbox("Snap To Grid", &snapToGrid);

			if (ImGui::Button("Add Enemy") || ImGui::IsKeyPressed(ImGuiKey_E) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
				addEnemy(EnemySpawnPoint(def->name, selectPos));

				selectPos = {};
			}
		}


		ImGui::End();
	}

	if (enemyEditWindow) {
		ImGui::Begin("Enemy Editing");

		if (eSelectedIndex < 0 || enemySpawnPoints.size() == 0) {
			for (int i = 0; i < enemySpawnPoints.size(); i++) {
				std::string label = "Enemy " + std::to_string(i);
				if (ImGui::Selectable(label.c_str(), eSelectedIndex == i)) {
					eSelectedIndex = i;
				}
			}
		}
		else {
			if (eSelectedIndex >= enemySpawnPoints.size())
				eSelectedIndex = enemySpawnPoints.size() - 1;

			auto& enemySP = enemySpawnPoints[eSelectedIndex];
			if (ImGui::Button("Exit")) {
				eSelectedIndex = -1;
			}

			if (ImGui::Button("Duplicate")) {
				duplicateEnemy(eSelectedIndex);
			}

			sf::Vector2f pos = enemySP.GetPosition();

			if (ImGui::InputFloat2("X, Y", &pos.x, "%.1f")) {
				pos = snapToGridFunc(pos, gridSize, snapToGrid);
				if (pos != enemySP.GetPosition())
					moveEnemy(eSelectedIndex, enemySP.GetPosition(), pos);
			}

			if (strEnemyTxNames[currentItem] != enemySP.GetName()) {
				for (int i = 0; i < strEnemyTxNames.size(); i++) {
					if (strEnemyTxNames[i] == enemySP.GetName()) {
						currentItem = i;
						break;
					}
				}
			}

			if (ImGui::Combo("Enemy Type", &currentItem, enemyTxNames.data(), enemyTxNames.size())) {
				changeEnemyType(eSelectedIndex, enemySP.GetName(), strEnemyTxNames[currentItem]);
			}

			auto* def = enemyManager.getEnemy(enemySP.GetName());
			if (def) {
				auto& textureAtlas = textures.get(def->textureAdress);
				sf::Sprite preview(textureAtlas, def->rect);
				
				static float scale = 3.f;
				ImGui::SliderFloat("Set Scale", &scale, 1.f, 10.f, "%.1f");
				preview.setScale(scale, scale);
				
				ImGui::Image(preview);
			}

			if (ImGui::Button("Delete Enemy")) {
				deleteEnemy(eSelectedIndex);
			}
		}

		ImGui::End();
	}

#pragma endregion

#pragma region Backgrounds

	if (backgroundWindow) {
		ImGui::Begin("Background");

		static bool add = false;
		if (!add) {
			if (ImGui::Button("+ Add Background")) {
				add = true;
				bSelectedIndex = -1;
			}
		}

		if (add) {
			if (ImGui::Button("Exit")) add = false;

			static sf::Vector2f backgroundSize;
			static float parllax = 1.f;
			ImGui::InputFloat2("Size", &backgroundSize.x, "%.1f");
			ImGui::InputFloat("Parllax", &parllax);
			
			static std::string label = "Choose Texture";

			if (ImGui::Button(label.c_str())) {
				selectTexture("backgrounds");
			}

			static std::string backgroundTexPath;
			if (ImGuiFileDialog::Instance()->Display("ChooseTextureDlgKey")) {
				if (ImGuiFileDialog::Instance()->IsOk()) {
					std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

					backgroundTexPath = fileFinding(filePathName);

					label = "Choose Texture (" + backgroundTexPath + ")";

				}

				ImGuiFileDialog::Instance()->Close();
			}
			
			if (ImGui::Button("Add Background")) {
				if (backgroundTexPath != std::string()) {
					addBackground(Background(&textures.get(backgroundTexPath), backgroundSize, parllax, backgroundTexPath));

					backgroundSize = {};
					add = false;
				}
			}

		}
		else {
			if (bSelectedIndex < 0 || backgrounds.size() == 0) {
				for (int i = 0; i < backgrounds.size(); i++) {
					std::string label = "Background " + std::to_string(i);
					if (ImGui::Selectable(label.c_str(), bSelectedIndex == i)) {
						bSelectedIndex = i;
					}
				}
			}
			else {
				if (bSelectedIndex >= backgrounds.size()) bSelectedIndex = backgrounds.size() - 1;
				
				auto& background = backgrounds[bSelectedIndex];

				if (ImGui::Button("Exit")) bSelectedIndex = -1;

				auto pos = background.GetPosition();
				auto size = background.GetSize();
				auto parllax = background.parlaxStrength;

				if (ImGui::InputFloat2("Position", &pos.x, "%.1f")) {
					if (pos != background.GetPosition()) {
						background.SetPosition(pos);
					}
				}
				if (ImGui::InputFloat2("Size", &size.x, "%.1f")) {
					if (size != background.GetSize()) {
						changeBackgroundSize(background, size);
					}
				}
				if (ImGui::InputFloat("Parllax", &parllax)) {
					if (parllax != background.parlaxStrength) { 
						changeParllax(background, parllax);
					}
				}
				if (ImGui::Button("Delete")) {
					deleteBackground(bSelectedIndex);
				}
				
			}
		}

		ImGui::End();
	}

#pragma endregion

#pragma region Checkpoints

	if (playerCheckpointsWindow) {
		ImGui::Begin("Checkpoints");
		
		static bool add = false;

		if (!add) {
			if (ImGui::Button("+ Add Checkpoint")) {
				add = true;
				cSelectedIndex = -1;
			}
		}

		if (add) {
			static std::string name = "spawn";
			ImGui::InputText("Checkpoint Name", &name);
			
			if (ImGui::InputFloat2("Position", &selectPos.x, "%.1f")) {
				selectPos = snapToGridFunc(selectPos, gridSize, snapToGrid);
			}

			if (ImGui::Button("Add Checkpoint")) {
				//checkpoints.push_back(Checkpoint(selectPos, name));
				addCheckpoint(Checkpoint(selectPos, name));
				add = false;
			}
		}
		else {
			if (cSelectedIndex < 0 || checkpoints.size() == 0) {
				for (int i = 0; i < checkpoints.size(); i++) {
					std::string label = "Background " + std::to_string(i);
					if (ImGui::Selectable(label.c_str(), cSelectedIndex == i)) {
						cSelectedIndex = i;
					}
				}
			}
			else {
				if (cSelectedIndex >= checkpoints.size()) cSelectedIndex = checkpoints.size() - 1;

				auto& checkpoint = checkpoints[cSelectedIndex];

				if (ImGui::Button("Exit")) cSelectedIndex = -1;

				auto pos = checkpoint.GetPosition();
				static std::string name = checkpoint.GetName();
				static bool changing = false;

				if (!changing && name != checkpoint.GetName()) name = checkpoint.GetName();

				if (ImGui::InputFloat2("Position", &pos.x, "%.1f")) {
					pos = snapToGridFunc(pos, gridSize, snapToGrid);
					if (pos != checkpoint.GetPosition()) {
						moveCheckpoint(checkpoint, pos);
					}
				}
				if (ImGui::InputText("Name", &name)) changing = true;
				if (ImGui::Button("Submit Name")) {
					if (name != checkpoint.GetName()) {
						changeCheckpointName(checkpoint, name);
						changing = false;
					}
				}

				if (ImGui::Button("Delete Checkpoint")) {
					deleteCheckpoint(cSelectedIndex);
				}
			}
		}

		ImGui::End();
	}

#pragma endregion


#pragma endregion

}

void EditorState::render(sf::RenderWindow& window) {
	
	window.setView(view);

	for (auto& background : backgrounds) {
		background.Draw(window);
	}

	if(snapToGrid)
		drawGrid(window, gridSize);

	for (auto& platform : platforms) {
		platform.Draw(window);
	}

	for (auto& enemySpawnPoint : enemySpawnPoints) {
		enemySpawnPoint.draw(window);
	}

	for (auto& checkpoint : checkpoints) {
		checkpoint.Draw(window);
	}

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




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

	//vertik·lne Ëiary
	for (float x = std::floor(left / gridSize) * gridSize; x < right; x += gridSize) {
		lines.append(sf::Vertex(sf::Vector2f(x, top), sf::Color(80, 80, 80)));
		lines.append(sf::Vertex(sf::Vector2f(x, bottom), sf::Color(80, 80, 80)));
	}

	//horizont·lne Ëiary
	for (float y = std::floor(top / gridSize) * gridSize; y < bottom; y += gridSize) {
		lines.append(sf::Vertex(sf::Vector2f(left, y), sf::Color(80, 80, 80)));
		lines.append(sf::Vertex(sf::Vector2f(right, y), sf::Color(80, 80, 80)));
	}
	
	window.draw(lines);
}

std::string EditorState::normalizePath(std::string path)
{
	std::replace(path.begin(), path.end(), '\\', '/');

	return path;
}

std::string EditorState::fileFinding(const std::string& filePathName) {
	if (filePathName.rfind(".json") != std::string::npos) {

		size_t dirPos = filePathName.rfind("\\levels\\");
		
		std::string filePath = filePathName.substr(dirPos, filePathName.size() - dirPos);

		return normalizePath(filePath);
	}

	if (filePathName.rfind(".png") != std::string::npos) {
		size_t dirPos = filePathName.rfind("\\backgrounds\\");
		
		std::string filePath = filePathName.substr(dirPos, filePathName.size() - dirPos);

		return normalizePath(filePath);
	}

	return std::string();
}

void EditorState::clearLevel() {
	platforms.clear();
	enemySpawnPoints.clear();
	backgrounds.clear();
	checkpoints.clear();
}

void EditorState::save() {
	std::ofstream save(RESOURCES_PATH + currentFilePath);

	nlohmann::json j;
	j["platform"] = Serializer::savePlatforms(platforms);
	j["enemy"] = Serializer::saveEnemySpawnPoints(enemySpawnPoints);
	j["background"] = Serializer::saveBackgrounds(backgrounds);
	j["checkpoint"] = Serializer::saveCheckpoints(checkpoints);
	save << j.dump(4);

	save.close();

	isSaved = true;
}

void EditorState::saveAs() {
	IGFD::FileDialogConfig config;
	config.path = std::string(resourcesPath) + "levels";

	ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File As", ".json", config);
}

void EditorState::loadLevel() {
	IGFD::FileDialogConfig config;
	config.path = std::string(resourcesPath) + "levels";
	ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".json", config);
}

void EditorState::load() {
	std::ifstream file(RESOURCES_PATH + currentFilePath);

	if (!file.is_open()) {
		std::cout << "File " << RESOURCES_PATH + currentFilePath << "\t is not opened";
		return;
	}
	else {
		nlohmann::json j;
		file >> j;

		platforms.clear();
		Serializer::loadPlatforms(j, platforms, textures, tileManager);

		enemySpawnPoints.clear();
		Serializer::loadEnemySpawnPoints(j, enemySpawnPoints);

		backgrounds.clear();
		Serializer::loadBackgrounds(j, backgrounds, textures);

		checkpoints.clear();
		Serializer::loadCheckpoints(j, checkpoints);

		file.close();

		isSaved = true;
	}
}

void EditorState::selectTexture(const std::string& dirPath) {
	IGFD::FileDialogConfig config;
	config.path = std::string(resourcesPath) + dirPath;
	ImGuiFileDialog::Instance()->OpenDialog("ChooseTextureDlgKey", "Choose Texture", ".png", config);
}

void EditorState::addAction(std::unique_ptr<EditorAction> action) {
	//vykonaj akciu
	action->redo();

	//uloû do undo stacku
	undoStack.push(std::move(action));

	//vyËisti redo stack
	while (!redoStack.empty())
		redoStack.pop();

	isSaved = false;
}

void EditorState::undo() {
	if (!undoStack.empty()) {
		auto action = std::move(undoStack.top());
		undoStack.pop();

		action->undo();
		redoStack.push(std::move(action));

		isSaved = false;
	}
}

void EditorState::redo() {
	if (!redoStack.empty()) {
		auto action = std::move(redoStack.top());
		redoStack.pop();

		action->redo();
		undoStack.push(std::move(action));

		isSaved = false;
	}
}

void EditorState::addPlatform(const Platform& platform) {
	auto action = std::make_unique<AddPlatformAction>(platforms, platform, platforms.size());
	addAction(std::move(action));
}

void EditorState::duplicatePlatform(int& selectedIndex) {
	if (selectedIndex >= 0) {
		auto& platform = platforms[selectedIndex];

		sf::Vector2f pos = platform.GetPosition();
		sf::Vector2f size = platform.GetSize();

		addPlatform(Platform(
			size,
			sf::Vector2f(pos.x + gridSize, pos.y + gridSize),
			&textures.get(tileManager.getTile(platform.GetTexture())->textureAdress),
			tileManager.getTile(platform.GetTexture())->rect,
			tileManager.getTile(platform.GetTexture())->name
		));
		
		selectedIndex = platforms.size() - 1;
	}
}

void EditorState::deletePlatform(int& selectedIndex) {
	if (selectedIndex >= 0) {

		auto action = std::make_unique<DeletePlatformAction>(platforms, selectedIndex);
		addAction(std::move(action));

		selectedIndex = -1;
	}
}

void EditorState::movePlatform(const int& selectedIndex, sf::Vector2f oldPos, sf::Vector2f newPos) {
	auto action = std::make_unique<MovePlatformAction>(platforms, selectedIndex, oldPos, newPos);
	addAction(std::move(action));
}

void EditorState::resizePlatform(const int& selectedIndex, sf::Vector2f oldSize, sf::Vector2f newSize) {
	auto action = std::make_unique<ResizePlatformAction>(platforms, selectedIndex, oldSize, newSize);
	addAction(std::move(action));
}

void EditorState::changePlatformTile(const int& selectedIndex, const std::string& oldTile, const std::string& newTile) {
	auto action = std::make_unique<ChangeTileAction>(platforms, selectedIndex, oldTile, newTile, tileManager);
	addAction(std::move(action));
}

void EditorState::addEnemy(const EnemySpawnPoint& enemySpawnPoint) {
	auto action = std::make_unique<AddEnemyAction>(enemySpawnPoints, enemySpawnPoint, enemySpawnPoints.size());
	addAction(std::move(action));
}

void EditorState::moveEnemy(const int& selectedIndex, sf::Vector2f oldPos, sf::Vector2f newPos) {
	auto action = std::make_unique<MoveEnemyAction>(enemySpawnPoints, selectedIndex, oldPos, newPos);
	addAction(std::move(action));
}

void EditorState::deleteEnemy(int& selectedIndex) {
	if (selectedIndex >= 0) {

		auto action = std::make_unique<DeleteEnemyAction>(enemySpawnPoints, selectedIndex);
		addAction(std::move(action));

		selectedIndex = -1;
	}
}

void EditorState::changeEnemyType(const int& selectedIndex, const std::string& oldType, const std::string& newType) {
	auto action = std::make_unique<ChangeEnemyTypeAction>(enemySpawnPoints[selectedIndex], oldType, newType, enemyManager);
	addAction(std::move(action));
}

void EditorState::duplicateEnemy(int& selectedIndex) {
	if (selectedIndex >= 0) {
		auto& enemySP = enemySpawnPoints[selectedIndex];

		sf::Vector2f pos = enemySP.GetPosition();

		addEnemy(EnemySpawnPoint(enemySP.GetName(), sf::Vector2f(pos.x + gridSize, pos.y + gridSize)));

		selectedIndex = enemySpawnPoints.size() - 1;
	}
}

void EditorState::addBackground(const Background& background){
	auto action = std::make_unique<AddBackgroundAction>(backgrounds, background, backgrounds.size());
	addAction(std::move(action));
}

void EditorState::deleteBackground(int& selectedIndex) {
	if (selectedIndex >= 0) {
		auto action = std::make_unique<DeleteBackgroundAction>(backgrounds, backgrounds[selectedIndex], selectedIndex);
		addAction(std::move(action));

		selectedIndex = -1;
	}

}

void EditorState::changeBackgroundSize(Background& background, sf::Vector2f newSize) {
	auto action = std::make_unique<ChangeBackgroundSizeAction>(background, background.GetSize(), newSize);
	addAction(std::move(action));
}

void EditorState::changeParllax(Background& background, float newParllax) {
	auto action = std::make_unique<ChangeParllaxStrengthAction>(background, background.parlaxStrength, newParllax);

	addAction(std::move(action));
}

void EditorState::addCheckpoint(const Checkpoint& checkpoint) {
	auto action = std::make_unique<AddCheckpointAction>(checkpoints, checkpoint, checkpoints.size());

	addAction(std::move(action));
}

void EditorState::moveCheckpoint(Checkpoint& checkpoint, sf::Vector2f newPos) {
	auto action = std::make_unique<MoveCheckpointAction>(checkpoint, checkpoint.GetPosition(), newPos);

	addAction(std::move(action));
}

void EditorState::deleteCheckpoint(int& selectetIndex) {
	if (selectetIndex >= 0) {
		auto action = std::make_unique<DeleteCheckpointAction>(checkpoints, checkpoints[selectetIndex], selectetIndex);

		addAction(std::move(action));

		selectetIndex = -1;
	}
}

void EditorState::changeCheckpointName(Checkpoint& checkpoint, const std::string& newName) {
	auto action = std::make_unique<ChangeCheckpointNameAction>(checkpoint, checkpoint.GetName(), newName);

	addAction(std::move(action));
}
