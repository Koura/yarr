#pragma once
#include "IRenderer.h"

class Scene;

class Renderer : public IRenderer
{
public:
	Renderer();
	Renderer(const Renderer&);
	~Renderer();
	bool Initialize(int, int);
	void Shutdown();
	bool Frame();
	void SetScene(Scene*);
	Scene* GetScene();
private:
	bool Render(); 
	Scene* m_scene;
};

