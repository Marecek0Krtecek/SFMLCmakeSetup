#pragma once
#include <memory>

struct EditorAction
{
	virtual ~EditorAction() = default;
	virtual void undo() = 0;
	virtual void redo() = 0;
};