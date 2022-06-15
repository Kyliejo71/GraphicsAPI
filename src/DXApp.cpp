#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_Color.h"
#include "ShaderTexture.h"
#include "ShaderTextureLight.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_TextureLight.h"
#include "SkyBox.h"
#include "GraphicObject_ColorLight.h"

void DXApp::InitDemo()
{
	pShaderTex = new ShaderTexture(md3dDevice);
	pShaderColorLight = new ShaderColorLight(md3dDevice);
	pShaderTextureLight = new ShaderTextureLight(md3dDevice);

	pTerrainTex = new Texture(md3dDevice, L"../Assets/Textures/grass2.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pTerrain = new TerrainModel(md3dDevice, L"../Assets/Textures/HMTest.tga", 500, 150, -5, 30, 30);

	pSB = new SkyBox(md3dDevice, 600);
	pSBTex = new Texture(md3dDevice, L"../Assets/Textures/SBNight6.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	
	mWorld = Matrix(IDENTITY);

	//STATUE
	pStatue = new Model(md3dDevice, "../Assets/Models/horse.azul");
	mStatueWorld = Matrix(SCALE, 0.5, 0.5, 0.5) * Matrix(ROT_Y, 80) * Matrix(TRANS, 150, 9, 140);
	pGO_Statue = new GraphicObject_ColorLight(pShaderColorLight, pStatue);
	pGO_Statue->SetWorld(mStatueWorld);
	pGO_Statue->SetMaterial(Colors::DarkGray, Colors::DarkGray, Colors::DarkGray, 0);
	pGO_Statue->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	//GEMS
	pGem = new Model(md3dDevice, "../Assets/Models/Gem.azul");
	mGem1 = Matrix(SCALE, 0.25, 0.25, 0.25) * Matrix(TRANS, 30, 9, 25);
	mGem2 = Matrix(SCALE, 0.25, 0.25, 0.25) * Matrix(ROT_X, .5) * Matrix(TRANS, 35, 10, 25);
	mGem3 = Matrix(SCALE, 0.25, 0.25, 0.25) * Matrix(TRANS, 30, 9, 45);
	pGemTex = new Texture(md3dDevice, L"../Assets/Textures/Gem.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pGO_Gem = new GraphicObject_TextureLight(pShaderTextureLight, pGem);
	pGO_Gem->SetWorld(mGem1);
	pGO_Gem->SetTexture(pGemTex, 0);
	pGO_Gem->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Gem->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	pGO_Gem2 = new GraphicObject_TextureLight(pShaderTextureLight, pGem);
	pGO_Gem2->SetWorld(mGem2);
	pGO_Gem2->SetTexture(pGemTex, 0);
	pGO_Gem2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Gem2->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	pGO_Gem3 = new GraphicObject_TextureLight(pShaderTextureLight, pGem);
	pGO_Gem3->SetWorld(mGem3);
	pGO_Gem3->SetTexture(pGemTex, 0);
	pGO_Gem3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Gem3->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	//ORB
	pOrb = new Model(md3dDevice, Model::PreMadeModels::UnitSphere);
	pos2 = Vect(150, 11, 140);
	mOrb = Matrix(IDENTITY) * Matrix(TRANS, pos2);
	pGO_Orb = new GraphicObject_ColorLight(pShaderColorLight, pOrb);
	pGO_Orb->SetWorld(mOrb);
	pGO_Orb->SetMaterial(Colors::LightBlue, Colors::LightBlue, Colors::LightBlue, 0);

	//TREE
	pTree = new Model(md3dDevice, "../Assets/Models/Tree.azul");
	mTree = Matrix(SCALE, 0.1, 0.1, 0.1) * Matrix(TRANS, 100, 9, 130);
	pTreeTex1 = new Texture(md3dDevice, L"../Assets/Textures/Leaves.tga", D3D11_FILTER_MIN_MAG_MIP_LINEAR);
	pGO_Tree = new GraphicObject_TextureLight(pShaderTextureLight, pTree);
	pGO_Tree->SetWorld(mTree);
	pGO_Tree->SetTexture(pTreeTex1, 0);
	pGO_Tree->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Tree->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	mTree2 = Matrix(SCALE, 0.1, 0.1, 0.1) *Matrix(ROT_Y, 5) * Matrix(TRANS, 105, 5, 35);
	pGO_Tree2 = new GraphicObject_TextureLight(pShaderTextureLight, pTree);
	pGO_Tree2->SetWorld(mTree2);
	pGO_Tree2->SetTexture(pTreeTex1, 0);
	pGO_Tree2->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Tree2->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));
	mTree3 = Matrix(SCALE, 0.1, 0.1, 0.1) * Matrix(ROT_Y, 2) * Matrix(TRANS, 160, 10, 90);
	pGO_Tree3 = new GraphicObject_TextureLight(pShaderTextureLight, pTree);
	pGO_Tree3->SetWorld(mTree3);
	pGO_Tree3->SetTexture(pTreeTex1, 0);
	pGO_Tree3->SetMaterial(Colors::White, Colors::White, Vect(1, 1, 1, 100), 0);
	pGO_Tree3->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	//ROCK
	pRock = new Model(md3dDevice, "../Assets/Models/Rock_9.azul");
	mRock = Matrix(SCALE, 0.05, 0.05, 0.05) * Matrix(ROT_X, 5) * Matrix(TRANS, 130, 9, 70);
	pGO_Rock = new GraphicObject_ColorLight(pShaderColorLight, pRock);
	pGO_Rock->SetWorld(mRock);
	pGO_Rock->SetMaterial(Colors::Beige, Colors::Beige, Colors::Beige, 0);
	pGO_Rock->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	// Initialize the projection matrix
	mCam.setPerspective(45, mClientWidth / (float)mClientHeight, 1.0f, 1000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(100, 20, 100), Vect(20, 15, 20));

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	mOrb *= Matrix(ROT_Y, .0006f);
	pos2 = mOrb.get(MatrixRowType::ROW_3);
	pGO_Orb->SetWorld(mOrb);

	float camSpeed = 0.008f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.0005f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	Vect eyepos;
	mCam.getPos(eyepos);

	//SHADER TEXTURE
	pShaderTex->SetToContext(md3dImmediateContext);
	pShaderTex->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	//SKY BOX
	pShaderTex->SetTextureResourceAndSampler(pSBTex);
	pSB->SetToContext(md3dImmediateContext);
	pShaderTex->SendWorld(mWorld);
	pSB->Render(md3dImmediateContext);

	//SHADER COLOR LIGHT
	pShaderColorLight->SetSpotLightParameters(pos2, 4000, .5 * Vect(1, 0, 0),
		-pos2.getNorm(), 50,
		.2 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	pShaderColorLight->SetToContext(md3dImmediateContext);
	pShaderColorLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	//STATUE
	pGO_Statue->SetToContext(md3dImmediateContext);
	pGO_Statue->SendLightParameters(eyepos);
	pGO_Statue->SendFogData(110, 200, Colors::LightBlue);
	pGO_Statue->Render();

	//ORB
	pGO_Orb->SetToContext(md3dImmediateContext);
	pGO_Orb->SendLightParameters(eyepos);
	pGO_Orb->Render();

	//ROCK
	pGO_Rock->SetToContext(md3dImmediateContext);
	pGO_Rock->SendLightParameters(eyepos);
	pGO_Rock->SendFogData(2200, 200, Colors::LightBlue);
	pGO_Rock->Render();

	//SHADER TEXTURE LIGHT
	pShaderTextureLight->SetToContext(md3dImmediateContext);
	pShaderTextureLight->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTextureLight->SendLightParameters(eyepos);

	//TERRAIN
	pShaderTextureLight->SetTextureResourceAndSampler(pTerrainTex);
	pShaderTextureLight->SendWorldAndMaterial(mWorld, Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pShaderTextureLight->SendFogData(70, 200, Colors::LightBlue);
	pTerrain->Render(md3dImmediateContext);

	//GEM
	pGO_Gem->SetToContext(md3dImmediateContext);
	pGO_Gem->SendLightParameters(eyepos);
	pGO_Gem->SendFogData(110, 200, Colors::LightBlue);
	pGO_Gem->Render();
	pGO_Gem2->SetToContext(md3dImmediateContext);
	pGO_Gem2->SendLightParameters(eyepos);
	pGO_Gem2->SendFogData(110, 200, Colors::LightBlue);
	pGO_Gem2->Render();
	pGO_Gem3->SetToContext(md3dImmediateContext);
	pGO_Gem3->SendLightParameters(eyepos);
	pGO_Gem3->SendFogData(110, 200, Colors::LightBlue);
	pGO_Gem3->Render();

	//TREE
	pGO_Tree->SetToContext(md3dImmediateContext);
	pGO_Tree->SendLightParameters(eyepos);
	pGO_Tree->SendFogData(1010, 200, Colors::LightBlue);
	pGO_Tree->Render();
	pGO_Tree2->SetToContext(md3dImmediateContext);
	pGO_Tree2->SendLightParameters(eyepos);
	pGO_Tree2->SendFogData(600, 200, Colors::LightBlue);
	pGO_Tree2->Render();
	pGO_Tree3->SetToContext(md3dImmediateContext);
	pGO_Tree3->SendLightParameters(eyepos);
	pGO_Tree3->SendFogData(1010, 200, Colors::LightBlue);
	pGO_Tree3->Render();

	// Switches the display to show the now-finished back-buffer
	mSwapChain->Present(0, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{
	delete pShaderTex;
	delete pShaderColorLight;
	delete pShaderTextureLight;

	delete pTerrain;
	delete pTerrainTex;

	delete pSB;
	delete pSBTex;

	delete pStatue;
	delete pGO_Statue;

	delete pGem;
	delete pGemTex;
	delete pGO_Gem;
	delete pGO_Gem2;
	delete pGO_Gem3;

	delete pOrb;
	delete pGO_Orb;

	delete pTree;
	delete pTreeTex1;
	delete pGO_Tree;
	delete pGO_Tree2;
	delete pGO_Tree3;

	delete pRock;
	delete pGO_Rock;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = true;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}