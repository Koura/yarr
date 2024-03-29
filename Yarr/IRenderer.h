#pragma once

#include "Scene.h"

class IRenderer
{
public:
	IRenderer(){};
	IRenderer(const IRenderer&){};
	virtual ~IRenderer(){};

	virtual bool Initialize(int, int) = 0;
	virtual void Shutdown() = 0;
	virtual bool Frame() = 0;
	virtual void SetScene(Scene*) = 0;
	virtual Scene* GetScene() = 0;
private:
	virtual bool Render() = 0;
};