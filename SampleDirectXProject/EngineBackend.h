#pragma once

enum class EditorMode {
	EDITOR = 0,
	PLAY = 1,
	PAUSED = 2
};

class EngineBackend
{
public:
	EngineBackend();
	~EngineBackend();

	static EngineBackend* Get();
	static void Initialize();
	static void Destroy();

	void SetMode(EditorMode mode);
	void StartFrameStep();
	void EndFrameStep();
	bool InsideFrameStep();
	EditorMode GetMode() const;

private:
	bool frameStepping = false;
	static EngineBackend* instance;

	EditorMode editorMode = EditorMode::EDITOR;
};
