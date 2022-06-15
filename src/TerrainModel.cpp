#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);
	mWorld = Matrix(TRANS, -len / 2, ytrans, -len / 2);
	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	uint8_t h_val = hgtmap->pixels[pixel_width * (5 * side + 3)]; // the 'R' byte of the pixel at (3,5)


	// ** much work to add below **

	int nverts = side * side;
	int ntri = (side - 1) * (side - 1) * 2;

	StandardVertex* pVerts = new StandardVertex[nverts];
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];
	float imageScale = (len / side);
	float yscale(maxheight / 255);
	for (int i = 0; i < side; i++)
	{
		for (int j = 0; j < side; j++)
		{
			pVerts[int(i * side + j)].set(i, (hgtmap->pixels[TexelIndex(side, i, j)] * yscale), j,
				((RepeatU / (len - 1)) * i), ((RepeatV / (len - 1)) * j));
		}
	}
	Vect east;
	Vect west;
	Vect north;
	Vect south;

	//Vect northWest;
	//Vect northEast;
	//Vect southWest;
	//Vect southEast;

	Vect indexNorm;

	int triIndex = 0;

	for (int i = 0; i < side - 1; i++)
	{
		for (int j = 0; j < side - 1; j++)
		{
			pTriList[triIndex++].set(j + (side * i) + 1, j + side + (side * i), j + (side * i));
			pTriList[triIndex++].set(j + (side * i) + 1, j + side + (side * i) + 1, j + side + (side * i));


			if (i != 0 && j != 0 && i != side - 2 && j != side - 2)
			{
				west = pVerts[int(i * side + j)].Pos - pVerts[int((i - 1) * side + j)].Pos;
				east = pVerts[int(i * side + j)].Pos - pVerts[int((i + 1) * side + j)].Pos;
				north = pVerts[int(i * side + j)].Pos - pVerts[int(i * side) + (j + 1)].Pos;
				south = pVerts[int(i * side + j)].Pos - pVerts[int(i * side) + (j - 1)].Pos;

				//northWest = west.cross(north);
				//northEast = north.cross(east);
				//southWest = south.cross(west);
				//southEast = east.cross(south);
			}

		}
	}

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
	delete[] pVerts;
	delete[] pTriList;

}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

int TerrainModel::TexelIndex(int side, int x, int y) const
{
	return 4 * (y * side + x);
}
