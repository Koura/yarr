#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>

struct MyVec3
{
	float x;
	float y;
	float z;
};

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

struct VertexType
{
	MyVec3 position;
	Color color;
};

class Model
{

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
};

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(char*);
	void Shutdown();
	int GetIndexCount();
private:
	bool LoadPlainModel(char*);
	void ReleaseModel();
private:
	int m_vertexCount, m_indexCount;
	ModelType* m_model;
};
#endif