#include "Model.h"

Model::Model()
{
	m_model = 0;
}

Model::Model(const Model& other)
{
}

Model::~Model()
{
}

bool Model::Initialize(char* filename)
{
	bool result;
	result = LoadPlainModel(filename);
	if(!result)
	{
		return false;
	}
	return true;
}

int Model::GetIndexCount()
{
	return m_indexCount;
}

void Model::Shutdown()
{
	ReleaseModel();
	return;
}

bool Model::LoadPlainModel(char* filename)
{
	std::ifstream fin;
	char input;
	int i;
	fin.open(filename);
	if(fin.fail())
	{
		return false;
	}
	fin.get(input);
	while(input != ':')
	{
		if(!fin.eof())
		{
			fin.get(input);
		} 
		else
		{
			return false;
		}
	}
	fin >> m_vertexCount;
	m_indexCount = m_vertexCount;
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);
	for(i=0; i<m_vertexCount; i++)
	{
		if(!fin.eof())
		{
			fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		}
		else
		{
			return false;
		}
	}
	fin.close();
	return true;
}

void Model::ReleaseModel()
{
	if(m_model)
	{
		delete m_model;
		m_model = 0;
	}
	return;
}