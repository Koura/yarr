#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

#include "IRenderer.h"
#include "ColorShader.h"
#include <D3D10.h>
#include <DXGI.h>
#include <D3DX10.h>


const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3D10Class : public IRenderer
{
public:
	D3D10Class();
	D3D10Class(const D3D10Class&);
	~D3D10Class();
	bool Initialize(int, int);
	void Shutdown();
	bool Frame();

	void BeginScene(float, float, float, float);
	void EndScene();
	ID3D10Device* GetDevice();
	void SetScene(Scene*);

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);
	void SetHWND(HWND);
	bool InitializeShader(WCHAR*);

private:
	bool Render();
	void SetUpCameraView();
private:
	bool m_vsync_enabled;
	IDXGISwapChain* m_swapChain;
	ID3D10Device* m_device;
	ID3D10RenderTargetView* m_renderTargetView;
	ID3D10Texture2D* m_depthStencilBuffer;
	ID3D10DepthStencilState* m_depthStencilState;
	ID3D10DepthStencilView* m_depthStencilView;
	ID3D10RasterizerState* m_rasterState;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;
	D3DXMATRIX m_orthoMatrix;
	HWND m_hwnd;
	Scene* m_scene;
	ColorShader* m_colorShader;
	Camera* m_camera;
};
#endif