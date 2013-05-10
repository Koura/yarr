#ifndef _MODEL_H_
#define _MODEL_H_

#include <fstream>

class Model
{

struct ModelType
{
	float x, y, z;
    float r, g, b, a;
};

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(char*);
	void Shutdown();
	virtual int GetIndexCount();
private:
	bool LoadPlainModel(char*);
	void ReleaseModel();
protected:
	int m_vertexCount, m_indexCount;
	ModelType* m_model;
};
#endif