#ifndef _COLORSHADER_H_
#define _COLORSHADER_H_

#include <D3D10.h>
#include <D3DX10math.h>
#include <fstream>

class ColorShader
{
public:
	ColorShader();
	ColorShader(const ColorShader&);
	~ColorShader();
	bool Initialize(ID3D10Device*, HWND, WCHAR*);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);
	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10Effect* m_effect;
	ID3D10EffectTechnique* m_technique;
	ID3D10InputLayout* m_layout;

	ID3D10EffectMatrixVariable* m_worldMatrixPtr;
	ID3D10EffectMatrixVariable* m_viewMatrixPtr;
	ID3D10EffectMatrixVariable* m_projectionMatrixPtr;
};

#endif