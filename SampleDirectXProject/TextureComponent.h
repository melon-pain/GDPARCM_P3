#pragma once
#include "Component.h"

class PixelShader;

class Texture;

class TextureComponent : public Component
{
public:
	TextureComponent();
	~TextureComponent() override;

public:
	void Start() override;
	void SetTexture(Texture* inTexture);
	Texture* GetTexture();
protected:
	PixelShader* m_ps = nullptr;
private:
	Texture* texture;
protected:
	friend class Texture;
};

