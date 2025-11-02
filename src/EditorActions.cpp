#include "EditorActions.h"

AddPlatformAction::AddPlatformAction(std::vector<Platform>& platforms, const Platform& newPlatform, size_t index) :
	platforms(platforms),
	platform(newPlatform),
	index(index)
{

}

void AddPlatformAction::undo() {
	platforms.erase(platforms.begin() + index);
}

void AddPlatformAction::redo() {
	platforms.insert(platforms.begin() + index, platform);
}

DeletePlatformAction::DeletePlatformAction(std::vector<Platform>& platforms, size_t index) :
	platforms(platforms),
	index(index),
	platform(platforms[index])
{

}

void DeletePlatformAction::undo() {
	platforms.insert(platforms.begin() + index, platform);
}

void DeletePlatformAction::redo() {
	platforms.erase(platforms.begin() + index);
}

MovePlatformAction::MovePlatformAction(std::vector<Platform>& platforms, size_t index, sf::Vector2f oldPos, sf::Vector2f newPos) :
	platforms(platforms),
	index(index),
	oldPos(oldPos),
	newPos(newPos)
{

}

void MovePlatformAction::undo() {
	platforms[index].SetPosition(oldPos);
}

void MovePlatformAction::redo() {
	platforms[index].SetPosition(newPos);
}

ResizePlatformAction::ResizePlatformAction(std::vector<Platform>& platforms, size_t index, sf::Vector2f oldSize, sf::Vector2f newSize) :
	platforms(platforms),
	index(index),
	oldSize(oldSize),
	newSize(newSize)
{

}

void ResizePlatformAction::undo() {
	platforms[index].SetSize(oldSize);
}

void ResizePlatformAction::redo() {
	platforms[index].SetSize(newSize);
}

ChangeTileAction::ChangeTileAction(std::vector<Platform>& platforms, size_t index, std::string oldTile, std::string newTile, TileManager& tileManager) :
	platforms(platforms),
	index(index),
	oldTile(oldTile),
	newTile(newTile),
	tileManager(tileManager)
{

}

void ChangeTileAction::undo() {
	platforms[index].SetTextureRect(tileManager.getTile(oldTile)->rect);
	platforms[index].SetTileName(tileManager.getTile(oldTile)->name);
}

void ChangeTileAction::redo() {
	platforms[index].SetTextureRect(tileManager.getTile(newTile)->rect);
	platforms[index].SetTileName(tileManager.getTile(newTile)->name);
}

AddEnemyAction::AddEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, const EnemySpawnPoint& enemySpawnPoint, size_t index) :
	enemySpawnPoints(enemySpawnPoints),
	enemySpawnPoint(enemySpawnPoint),
	index(index)
{

}

void AddEnemyAction::undo() {
	enemySpawnPoints.erase(enemySpawnPoints.begin() + index);
}

void AddEnemyAction::redo() {
	enemySpawnPoints.insert(enemySpawnPoints.begin() + index, enemySpawnPoint);
}

DeleteEnemyAction::DeleteEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, size_t index) :
	enemySpawnPoints(enemySpawnPoints),
	index(index),
	enemySpawnPoint(enemySpawnPoints[index]) 
{

}

void DeleteEnemyAction::undo() {
	enemySpawnPoints.insert(enemySpawnPoints.begin() + index, enemySpawnPoint);
}

void DeleteEnemyAction::redo() {
	enemySpawnPoints.erase(enemySpawnPoints.begin() + index);
}

MoveEnemyAction::MoveEnemyAction(std::vector<EnemySpawnPoint>& enemySpawnPoints, size_t index, sf::Vector2f oldPos, sf::Vector2f newPos) :
	enemySpawnPoints(enemySpawnPoints),
	index(index),
	oldPos(oldPos),
	newPos(newPos)
{

}

void MoveEnemyAction::undo() {
	enemySpawnPoints[index].SetPosition(oldPos);
}

void MoveEnemyAction::redo() {
	enemySpawnPoints[index].SetPosition(newPos);
}

ChangeEnemyTypeAction::ChangeEnemyTypeAction(EnemySpawnPoint& enemySpawnPoint, std::string oldName, std::string newName, EnemyManager& enemyManager) :
	enemySpawnPoint(enemySpawnPoint),
	oldName(oldName),
	newName(newName),
	enemyManager(enemyManager)
{

}

void ChangeEnemyTypeAction::undo() {
	enemySpawnPoint.SetName(oldName);
}

void ChangeEnemyTypeAction::redo() {
	enemySpawnPoint.SetName(newName);
}

AddBackgroundAction::AddBackgroundAction(std::vector<Background>& backgrounds, const Background& background, size_t index) :
	backgrounds(backgrounds),
	background(background),
	index(index)
{

}

void AddBackgroundAction::undo() {
	backgrounds.erase(backgrounds.begin() + index);
}

void AddBackgroundAction::redo() {
	backgrounds.insert(backgrounds.begin() + index, background);
}

DeleteBackgroundAction::DeleteBackgroundAction(std::vector<Background>& backgrounds, const Background& background, size_t index) :
	backgrounds(backgrounds),
	background(background),
	index(index)
{

}

void DeleteBackgroundAction::undo() {
	backgrounds.insert(backgrounds.begin() + index, background);
}

void DeleteBackgroundAction::redo() {
	backgrounds.erase(backgrounds.begin() + index);
}

ChangeBackgroundSizeAction::ChangeBackgroundSizeAction(Background& background, const sf::Vector2f& oldSize, const sf::Vector2f& newSize) :
	background(background),
	oldSize(oldSize),
	newSize(newSize)
{

}

void ChangeBackgroundSizeAction::undo() {
	background.SetSize(oldSize);
}

void ChangeBackgroundSizeAction::redo() {
	background.SetSize(newSize);
}

ChangeParllaxStrengthAction::ChangeParllaxStrengthAction(Background& background, const float& oldParllax, const float& newParllax) :
	background(background),
	oldParllax(oldParllax),
	newParllax(newParllax)
{

}

void ChangeParllaxStrengthAction::undo() {
	background.parlaxStrength = oldParllax;
}

void ChangeParllaxStrengthAction::redo(){
	background.parlaxStrength = newParllax;
}

AddCheckpointAction::AddCheckpointAction(std::vector<Checkpoint>& checkpoints, const Checkpoint& checkpoint, size_t index) :
	checkpoints(checkpoints),
	checkpoint(checkpoint),
	index(index)
{

}

void AddCheckpointAction::undo() {
	checkpoints.erase(checkpoints.begin() + index);
}

void AddCheckpointAction::redo() {
	checkpoints.insert(checkpoints.begin() + index, checkpoint);
}

DeleteCheckpointAction::DeleteCheckpointAction(std::vector<Checkpoint>& checkpoints, const Checkpoint& checkpoint, size_t index) :
	checkpoints(checkpoints),
	checkpoint(checkpoint),
	index(index)
{

}

void DeleteCheckpointAction::undo() {
	checkpoints.insert(checkpoints.begin() + index, checkpoint);
}

void DeleteCheckpointAction::redo() {
	checkpoints.erase(checkpoints.begin() + index);
}

MoveCheckpointAction::MoveCheckpointAction(Checkpoint& checkpoint, const sf::Vector2f& oldPos, const sf::Vector2f& newPos) :
	checkpoint(checkpoint),
	oldPos(oldPos),
	newPos(newPos)
{
	
}

void MoveCheckpointAction::undo() {
	checkpoint.SetPosition(oldPos);
}

void MoveCheckpointAction::redo() {
	checkpoint.SetPosition(newPos);
}

ChangeCheckpointNameAction::ChangeCheckpointNameAction(Checkpoint& checkpoint, const std::string& oldName, const std::string& newName) :
	checkpoint(checkpoint),
	oldName(oldName),
	newName(newName)
{
	
}

void ChangeCheckpointNameAction::undo() {
	checkpoint.SetName(oldName);
}

void ChangeCheckpointNameAction::redo() {
	checkpoint.SetName(newName);
}
