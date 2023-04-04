#include "ActionHistory.h"
#include "EditorAction.h"
#include "EngineBackend.h"

#include <iostream>

ActionHistory* ActionHistory::instance = nullptr;

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
	Clear();
}

ActionHistory* ActionHistory::Get()
{
    return instance;
}

void ActionHistory::Initialize()
{
    instance = new ActionHistory();
}

void ActionHistory::Destroy()
{
    delete instance;
}

void ActionHistory::RecordAction(GameObject* gameObject)
{
    if (EngineBackend::Get()->GetMode() == EditorMode::EDITOR) {
        EditorAction* editorAction = new EditorAction(gameObject);
        this->actionsPerformed.push(editorAction);

        std::cout << "Stored action " << gameObject->GetName() << "\n";
    }
}

bool ActionHistory::HasRemainingUndoActions()
{
    return !this->actionsPerformed.empty();
}

bool ActionHistory::HasRemainingRedoActions()
{
    return !this->actionsCancelled.empty();
}

EditorAction* ActionHistory::UndoAction()
{
	//do not undo actions during play mode.
	if (EngineBackend::Get()->GetMode() != EditorMode::EDITOR) {
		std::cout << "Cannot perform any undo during play. \n";
		return nullptr;
	}

	if (HasRemainingUndoActions()) {
		EditorAction* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(action);
		auto pos = action->GetStorePos();
		std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << "\n";
		return action;
	}
	else {
		std::cout << "No more actions remaining. \n";
		return nullptr;
	}
}

EditorAction* ActionHistory::RedoAction()
{
	//do not undo actions during play mode.
	if (EngineBackend::Get()->GetMode() != EditorMode::EDITOR) {
		std::cout << "Cannot perform any redo during play. \n";
		return NULL;
	}

	if (HasRemainingRedoActions()) {
		EditorAction* action = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(action);
		auto pos = action->GetStorePos();
		std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << "\n";
		return action;
	}
	else {
		std::cout << "No more actions remaining. \n";
		return NULL;
	}
}

void ActionHistory::Clear()
{
	while (HasRemainingUndoActions()) {
		EditorAction* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	while (HasRemainingRedoActions()) {
		EditorAction* action = this->actionsCancelled.top();
		delete action;
		this->actionsCancelled.pop();
	}
}
