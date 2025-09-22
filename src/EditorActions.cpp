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