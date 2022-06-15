// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_Color;
class GraphicObject_ColorLight;
class ShaderTexture;
class ShaderTextureLight;
class GraphicObject_Texture;
class GraphicObject_TextureLight;
class SkyBox;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	ShaderTexture* pShaderTex;
	ShaderColorLight* pShaderColorLight;
	ShaderTextureLight* pShaderTextureLight;
	
	TerrainModel* pTerrain;
	Texture* pTerrainTex;

	SkyBox* pSB;
	Texture* pSBTex;

	Matrix mWorld;

	//STATUE
	Model* pStatue;
	Matrix mStatueWorld;
	GraphicObject_ColorLight* pGO_Statue;

	//GEM
	Model* pGem;
	Texture* pGemTex;
	Matrix mGem1;
	Matrix mGem2;
	Matrix mGem3;
	GraphicObject_TextureLight* pGO_Gem;
	GraphicObject_TextureLight* pGO_Gem2;
	GraphicObject_TextureLight* pGO_Gem3;

	//ORB
	Model* pOrb;
	Matrix mOrb;
	GraphicObject_ColorLight* pGO_Orb;
	Vect pos2;

	//TREE
	Model* pTree;
	Matrix mTree;
	Matrix mTree2;
	Matrix mTree3;
	Texture* pTreeTex1;
	GraphicObject_TextureLight* pGO_Tree;
	GraphicObject_TextureLight* pGO_Tree2;
	GraphicObject_TextureLight* pGO_Tree3;

	//ROCK
	Model* pRock;
	Matrix mRock;
	GraphicObject_ColorLight* pGO_Rock;
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp