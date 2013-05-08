#pragma once

#include "Model.h"
#include "CRefCounted.h"
#include <d3d10.h>
#include <d3dx10math.h>

class DX10Model : public Model, public CRefCounted
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};
public:
	DX10Model();
	DX10Model(const DX10Model&);
	~DX10Model();
	bool Initialize(char*, ID3D10Device*, float, float, float, float);
	void Shutdown();
	void Render(ID3D10Device*);
private: 
	bool InitializeBuffers(ID3D10Device*, float, float, float , float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);
private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
};
