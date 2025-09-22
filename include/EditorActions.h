#pragma once
#include "EditorAction.h"
#include "Platform.h"
#include <vector>

struct AddPlatformAction : EditorAction
{
	AddPlatformAction(std::vector<Platform>& platforms, const Platform& newPlatform, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct DeletePlatformAction : EditorAction
{
	DeletePlatformAction(std::vector<Platform>& platforms, size_t index);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	Platform platform;
	size_t index;
};

struct MovePlatformAction : EditorAction
{
	MovePlatformAction(std::vector<Platform>& platforms, size_t index, sf::Vector2f oldPos, sf::Vector2f newPos);

	void undo() override;
	void redo() override;

private:
	std::vector<Platform>& platforms;
	size_t index;
	sf::Vector2f oldPos;
	sf::Vector2f newPos;
};