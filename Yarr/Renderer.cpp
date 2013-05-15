#include "Renderer.h"


Renderer::Renderer()
{
	m_scene=nullptr;
}

Renderer::Renderer(const Renderer& other)
{
}


Renderer::~Renderer()
{
}


bool Renderer::Initialize(int screenWidth, int screenHeight){
	return true;
}

void Renderer::Shutdown(){
}

bool Renderer::Frame(){
	return true;
}

void Renderer::SetScene(Scene* s){
	m_scene=s;
}


Scene* Renderer::GetScene(){
	return m_scene;
}

bool Renderer::Render(){
	return true;
}