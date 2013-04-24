#pragma once
#include "IRenderer.h"

class DxRenderer : public IRenderer
{
public:
	DxRenderer(){};
	DxRenderer(const DxRenderer&){};
	virtual ~DxRenderer(){};
private:
	virtual bool Render() = 0;
};
