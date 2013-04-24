#pragma once
#include "IRenderer.h"

class DxRenderer : public IRenderer
{
public:
	DxRenderer(){};
	DxRenderer(const DxRenderer&){};
	virtual ~DxRenderer(){};
	virtual bool InitializeShader(WCHAR*) = 0;
private:
	virtual bool Render() = 0;
};