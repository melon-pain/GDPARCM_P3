#pragma once
#include <vector>
#include <stack>

class EditorAction;
class GameObject;
class ActionHistory
{
public:
	ActionHistory();
	~ActionHistory();

	static ActionHistory* Get();
	static void Initialize();
	static void Destroy();

	void RecordAction(GameObject* gameObject);
	bool HasRemainingUndoActions();
	bool HasRemainingRedoActions();
	EditorAction* UndoAction();
	EditorAction* RedoAction();
	void Clear();

private:
	static ActionHistory* instance;

	std::stack<EditorAction*> actionsPerformed;
	std::stack<EditorAction*> actionsCancelled;
};

