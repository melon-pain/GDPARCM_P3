#pragma once
#include <string>
#include "IWorkerAction.h"

class IExecutionEvent;
class MeshLoader : public IWorkerAction
{
public:
	MeshLoader(std::wstring path, IExecutionEvent* executionEvent);
	~MeshLoader();
	// Inherited via IWorkerAction
	void Interrupt();
private:
	virtual void onStartTask() override;

	std::wstring Path;
	IExecutionEvent* exec;

	bool isInterrupted = false;
};

