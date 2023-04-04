#include "TextureComponent.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

TextureComponent::TextureComponent() : Component()
{
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Start()
{
	Component::Start();
}

void TextureComponent::SetTexture(Texture* inTexture)
{
	texture = inTexture;
}

Texture* TextureComponent::GetTexture()
{
	return texture;
}
