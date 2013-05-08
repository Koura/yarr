#include "DX10Model.h"

DX10Model::DX10Model()
{
}

DX10Model::DX10Model(const DX10Model& other)
{
}

DX10Model::~DX10Model()
{
}

bool DX10Model::Initialize(char* filename, ID3D10Device* device, float r, float g, float b, float a)
{
	bool result;
	result = Model::Initialize(filename);
	if(!result)
	{
		return false;
	}
	result = InitializeBuffers(device,r, g, b, a);
	if(!result)
	{
		return false;
	}
	return true;
}

void DX10Model::Shutdown()
{
	ShutdownBuffers();
	Model::Shutdown();
	return;
}

void DX10Model::Render(ID3D10Device* device)
{
	RenderBuffers(device);
	return;
}

bool DX10Model::InitializeBuffers(ID3D10Device* device, float r, float g, float b, float a)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}
	for(i=0; i<m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].color = D3DXVECTOR4(r, g, b, a);
		indices[i] = i;
	}
	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)* m_vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexData.pSysMem = vertices;
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}
	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexData.pSysMem = indices;
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}
	delete [] vertices;
	vertices = 0;
	delete [] indices;
	indices = 0;
	return true;
}

void DX10Model::ShutdownBuffers()
{
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

void DX10Model::RenderBuffers(ID3D10Device* device)
{
	unsigned int stride;
	unsigned int offset;
	stride = sizeof(VertexType);
	offset = 0;
	device->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	device->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return;
}
