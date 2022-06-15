#include "ShaderTextureLight.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

ShaderTextureLight::ShaderTextureLight(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/TextureLight.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
				  { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		  { "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));
	// fog buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_Fog);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferFogParams);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
}

ShaderTextureLight::~ShaderTextureLight()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBufferFogParams);
}

void ShaderTextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	dataLight.DirLight.Light.Ambient = amb;
	dataLight.DirLight.Light.Diffuse = dif;
	dataLight.DirLight.Light.Specular = sp;
	dataLight.DirLight.Direction = dir;
}

void ShaderTextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	dataLight.PntLight[dataLight.pntcount].Light.Ambient = amb;
	dataLight.PntLight[dataLight.pntcount].Light.Diffuse = dif;
	dataLight.PntLight[dataLight.pntcount].Light.Specular = sp;
	dataLight.PntLight[dataLight.pntcount].Position = pos;
	dataLight.PntLight[dataLight.pntcount].Attenuation = att;
	dataLight.PntLight[dataLight.pntcount].Range = r;
	dataLight.pntcount = count;
}

void ShaderTextureLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	dataLight.SptLight[dataLight.sptcount].Light.Ambient = amb;
	dataLight.SptLight[dataLight.sptcount].Light.Diffuse = dif;
	dataLight.SptLight[dataLight.sptcount].Light.Specular = sp;
	dataLight.SptLight[dataLight.sptcount].Position = pos;
	dataLight.SptLight[dataLight.sptcount].Attenuation = att;
	dataLight.SptLight[dataLight.sptcount].Range = r;
	dataLight.SptLight[dataLight.sptcount].Direction = dir;
	dataLight.SptLight[dataLight.sptcount].SpotExp = spotExp;
	dataLight.sptcount = count;
}

void ShaderTextureLight::SendLightParameters(const Vect& eyepos)
{
	Data_LightParams dl;
	dl.pntcount = dataLight.pntcount;
	dl.sptcount = dataLight.sptcount;
	dl.DirLight = dataLight.DirLight;
	for (int i = 0; i < 10; i++)
	{
		dl.PntLight[i] = dataLight.PntLight[i];
		dl.SptLight[i] = dataLight.SptLight[i];
	}
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderTextureLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}
void ShaderTextureLight::SendFogData(float start, float range, Vect c)
{
	Data_Fog df;
	df.FogStart = start;
	df.FogRange = range;
	df.Color = c;

	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &df, 0, 0);
}
void ShaderTextureLight::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->PSSetConstantBuffers(3, 1, &mpBufferFogParams);
	SendFogData(1000, 1, Vect(.2f, .2f, .2f, 1.0f));
}

void ShaderTextureLight::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(ShaderBase::GetContext());

}