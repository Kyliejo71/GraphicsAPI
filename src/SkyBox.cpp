#include "SkyBox.h"
#include <assert.h>
#include "File.h"
#include "d3dUtil.h"
#include "Model.h"
#include "SkyBoxTool.h"

void SkyBox::privLoadDataToGPU()
{
	// Vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StandardVertex) * numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pStdVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TriangleByIndex) * numTris;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = pTriList;
	hr = mDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));
}

SkyBox::SkyBox(ID3D11Device* dev, float size)
{
	mDevice = dev;
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;
	sizeOfBox = size;

	SkyBoxTool::CreateSkyBox(pStdVerts, numVerts, pTriList, numTris, sizeOfBox);


	privLoadDataToGPU();
}

SkyBox::~SkyBox()
{
	delete[] pTriList;
	delete[] pStdVerts;

	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer);
}

void SkyBox::SetToContext(ID3D11DeviceContext* context)
{
	UINT stride = sizeof(StandardVertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	context->DrawIndexed(numTris * 3, 0, 0);
}

