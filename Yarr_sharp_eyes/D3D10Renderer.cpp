#include "D3D10Renderer.h"

D3D10Renderer::D3D10Renderer()
{
	m_device = 0;
	m_swapChain = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
	m_colorShader = 0;
	m_camera = 0;
	m_model = 0;
}

D3D10Renderer::D3D10Renderer(const D3D10Renderer& other)
{
}

D3D10Renderer::~D3D10Renderer()
{
}

void D3D10Renderer::SetHWND(HWND hwnd)
{
	m_hwnd = hwnd;
}

bool D3D10Renderer::Initialize(int screenWidth, int screenHeight)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator;
	numModes = 0;
	i = 0;
	numerator = 0;
	denominator = 0;
	DXGI_MODE_DESC* displayModeList;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D10Texture2D* backBufferPtr;
	D3D10_TEXTURE2D_DESC depthBufferDesc;
	D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D10_VIEWPORT viewport;
	float fieldOfView, screenAspect;
	D3D10_RASTERIZER_DESC rasterDesc;
	m_vsync_enabled = true;
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
	{
		return false;
	}
	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
	{
		return false;
	}
	result = adapter->EnumOutputs(0, &adapterOutput);
	if(FAILED(result))
	{
		return false;
	}
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if(FAILED(result))
	{
		return false;
	}
	displayModeList = new DXGI_MODE_DESC[numModes];
	if(!displayModeList)
	{
		return false;
	}
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if(FAILED(result))
	{
		return false;
	}
	for(i=0; i<numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if(displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}
	delete[] displayModeList;
	displayModeList = 0;
	adapterOutput->Release();
	adapterOutput = 0;
	adapter->Release();
	adapter = 0;
	factory->Release();
	factory = 0;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	if(m_vsync_enabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	result = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, 
					       &swapChainDesc, &m_swapChain, &m_device);
	if(FAILED(result))
	{
		return false;
	}
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
	{
		return false;
	}
	result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
	if(FAILED(result))
	{
		return false;
	}
	backBufferPtr->Release();
	backBufferPtr = 0;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
	if(FAILED(result))
	{
		return false;
	}
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if(FAILED(result))
	{
		return false;
	}
	m_device->OMSetDepthStencilState(m_depthStencilState, 1);
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
	if(FAILED(result))
	{
		return false;
	}
	m_device->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D10_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D10_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if(FAILED(result))
	{
		return false;
	}
	m_device->RSSetState(m_rasterState);
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_device->RSSetViewports(1, &viewport);
	fieldOfView = (float)D3DX_PI / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_DEPTH);
	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	
	m_camera = new DxCamera();
	if(!m_camera)
	{
		return false;
	}
	m_camera->SetPosition(0.0f, 0.0f, -10.0f);
	//////LOAD THE SHADER
	InitializeShader(L"../Yarr_sharp_eyes/Resources/color.fx");
	m_model = new DX10Model();
	m_model->Initialize("../Game/Resources/Models/cube.txt", m_device, 0.5f, 1.0f, 0.0, 1.0);
	return true;
}

void D3D10Renderer::Shutdown()
{
	if(m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}
	if(m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}
	if(m_swapChain)
	{
		m_swapChain->SetFullscreenState(false, NULL);
	}
	if(m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = 0;
	}
	if(m_depthStencilView)
	{
		m_depthStencilView->Release();
		m_depthStencilView = 0;
	}
	if(m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = 0;
	}
	if(m_depthStencilBuffer)
	{
		m_depthStencilBuffer->Release();
		m_depthStencilBuffer = 0;
	}
	if(m_renderTargetView)
	{
		m_renderTargetView->Release();
		m_renderTargetView = 0;
	}
	if(m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = 0;
	}
	if(m_device)
	{
		m_device->Release();;
		m_device = 0;
	}
	return;
}

void D3D10Renderer::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
	m_device->ClearRenderTargetView(m_renderTargetView, color);
	m_device->ClearDepthStencilView(m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
	return;
}

void D3D10Renderer::EndScene()
{
	if(m_vsync_enabled)
	{
		m_swapChain->Present(1, 0);
	}
	else
	{
		m_swapChain->Present(0, 0);
	}
	return;
}

ID3D10Device* D3D10Renderer::GetDevice()
{
	return m_device;
}

void D3D10Renderer::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}


void D3D10Renderer::GetWorldMatrix(D3DXMATRIX& worldMatrix)
{
	worldMatrix = m_worldMatrix;
	return;
}


void D3D10Renderer::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}

bool D3D10Renderer::Frame()
{
	bool result;
	result = Render();
	if(!result)
	{
		return false;
	}
	return true;
}

bool D3D10Renderer::Render()
{
	D3DXMATRIX viewMatrix;
	BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	m_camera->Render();
	m_camera->GetViewMatrix(viewMatrix);
	std::set<IntrusivePtr<Entity> > entitySet = m_scene->GetEntitySet();
	Entity* ent = 0;
	POSITION modelPosition;
	DX10Model* model;
	for(std::set<IntrusivePtr<Entity> > ::const_iterator it = entitySet.begin(); it != entitySet.end(); ++it) 
	{
		ent = it->GetPtr();
		modelPosition = ent->GetPosition();
		D3DXMatrixTranslation(&m_worldMatrix, modelPosition.x, modelPosition.y, modelPosition.z);
		model = m_modelFactory->GetModelByName(ent->GetName());
		model->Render(m_device);
		m_colorShader->Render(m_device, model->GetIndexCount(), m_worldMatrix, viewMatrix, m_projectionMatrix);
	}
	EndScene();
	return true;
}

void D3D10Renderer::SetScene(Scene* scene)
{
	m_scene = scene;
}

void D3D10Renderer::SetModelFactory(DX10ModelFactory* modelFactory)
{
	m_modelFactory = modelFactory;
}

void D3D10Renderer::SetUpCameraView()
{
	D3DXVECTOR3 up, position, lookAt;
	D3DXVECTOR3 cameraRotation;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	D3DXVECTOR3 tempPos = m_camera->GetPosition();
	position.x = tempPos.x;
	position.y = tempPos.y;
	position.z = tempPos.z;
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	cameraRotation = m_camera->GetRotation();
	pitch = cameraRotation.x * 0.0174532925f;
	yaw = cameraRotation.y * 0.0174532925f;
	roll = cameraRotation.z * 0.0174532925f;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	lookAt = position + lookAt;
	D3DXMatrixLookAtLH(m_camera->SetViewMatrix(), &position, &lookAt, &up);
	return;
}

bool D3D10Renderer::InitializeShader(WCHAR* shaderfilename)
{
	m_colorShader = new ColorShader;
	if(!m_colorShader)
	{
		return false;
	}
	if(!m_colorShader->Initialize(m_device, m_hwnd, shaderfilename))
	{
		MessageBox(m_hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	return true;
}