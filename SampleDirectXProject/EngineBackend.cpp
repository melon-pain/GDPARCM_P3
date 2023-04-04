#include "EngineBackend.h"
#include "GameObjectManager.h"

EngineBackend* EngineBackend::instance = nullptr;

EngineBackend::EngineBackend()
{
}

EngineBackend::~EngineBackend()
{
}

EngineBackend* EngineBackend::Get()
{
    return instance;
}

void EngineBackend::Initialize()
{
    instance = new EngineBackend();
}

void EngineBackend::Destroy()
{
    delete instance;
}

void EngineBackend::SetMode(EditorMode mode)
{
    editorMode = mode;

    switch (editorMode)
    {
        case EditorMode::PLAY:
            GameObjectManager::Get()->SaveEditStates();
            break;
        case EditorMode::EDITOR:
            GameObjectManager::Get()->RestoreEditStates();
            break;
    }
}

void EngineBackend::StartFrameStep()
{
    frameStepping = true;
}

void EngineBackend::EndFrameStep()
{
    frameStepping = false;
}

bool EngineBackend::InsideFrameStep()
{
    return frameStepping;
}

EditorMode EngineBackend::GetMode() const
{
    return editorMode;
}
