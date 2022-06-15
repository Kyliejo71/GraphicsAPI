#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(+0.0f, +0.5f, +0.0f, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[1].set(+0.5f, -0.5f, +0.5f, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[2].set(+0.5f, -0.5f, -0.5f, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);

	pVerts[3].set(+0.0f, +0.5f, +0.0f, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);
	pVerts[4].set(+0.5f, -0.5f, -0.5f, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);
	pVerts[5].set(-0.5f, -0.5f, -0.5f, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);

	pVerts[6].set(+0.0f, +0.5f, +0.0f, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[7].set(-0.5f, -0.5f, -0.5f, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[8].set(-0.5f, -0.5f, +0.5f, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);

	pVerts[9].set(+0.0f, +0.5f, +0.0f, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);
	pVerts[10].set(-0.5f, -0.5f, +0.5f, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);
	pVerts[11].set(+0.5f, -0.5f, +0.5f, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);

	pVerts[12].set(-0.5f, -0.5f, -0.5f, Vect(0, -1, 0).norm(), Colors::Firebrick);
	pVerts[13].set(+0.5f, -0.5f, +0.5f, Vect(0, -1, 0).norm(), Colors::Firebrick);
	pVerts[14].set(-0.5f, -0.5f, +0.5f, Vect(0, -1, 0).norm(), Colors::Firebrick);
	pVerts[15].set(+0.5f, -0.5f, -0.5f, Vect(0, -1, 0).norm(), Colors::Firebrick);

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(3, 4, 5);
	pTriList[2].set(6, 7, 8);
	pTriList[3].set(9, 10, 11);
	pTriList[4].set(12, 13, 14);
	pTriList[5].set(12, 15, 13);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];
	int vind = 0;
	int tind = 0;

	//front
	pVerts[vind].set(+0.0f, +0.5f, +0.0f, +0.5f, 0, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[vind + 1].set(+0.5f, -0.5f, +0.5f, 0, 1, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[vind + 2].set(+0.5f, -0.5f, -0.5f, 1, 1, Vect(1, 0.5f, 0).norm(), Colors::Firebrick);
	pTriList[tind++].set(vind, vind + 1, vind + 2);
	vind += 3;
	//back
	pVerts[vind].set(+0.0f, +0.50f, +0.0f, +0.5f, 0, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);
	pVerts[vind + 1].set(+0.5f, -0.5f, -0.5f, 0, 1, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, Vect(0, 0.5f, -1).norm(), Colors::Firebrick);
	pTriList[tind++].set(vind, vind + 1, vind + 2);
	vind += 3;

	//right
	pVerts[vind].set(+0.0f, +0.50f, +0.0f, +0.5f, 0, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[vind + 1].set(-0.5f, -0.5f, -0.5f, 0, 1, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);
	pVerts[vind + 2].set(-0.5f, -0.5f, +0.5f, 1, 1, Vect(-1, 0.5f, 0).norm(), Colors::Firebrick);
	pTriList[tind++].set(vind, vind + 1, vind + 2);
	vind += 3;

	//left
	pVerts[vind].set(+0.0f, +0.50f, +0.0f, +0.5f, 0, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);
	pVerts[vind + 1].set(-0.5f, -0.50f, +0.50f, 0, 1, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);
	pVerts[vind + 2].set(+0.5f, -0.50f, +0.50f, 1, 1, Vect(0, 0.5f, 1).norm(), Colors::Firebrick);
	pTriList[tind++].set(vind, vind + 1, vind + 2);
	vind += 3;

	pVerts[vind].set(-0.5f, -0.5f, -0.5f, 0, 0, Vect(0, -1, 0), Colors::Firebrick);
	pVerts[vind + 1].set(+0.5f, -0.5f, +0.5f, 1, 1, Vect(0, -1, 0), Colors::Firebrick);
	pVerts[vind + 2].set(-0.5f, -0.5f, +0.5f, 1, 0, Vect(0, -1, 0), Colors::Firebrick);
	pVerts[vind + 3].set(+0.5f, -0.5f, -0.5f, 0, 1, Vect(0, -1, 0), Colors::Firebrick);
	pTriList[tind++].set(vind, vind + 1, vind + 2);
	pTriList[tind].set(vind, vind + 3, vind + 1);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = ((hslice + 1) * vslice) + 2;
	pVerts = new StandardVertex[nverts];
	ntri = (vslice * hslice) * 2;
	pTriList = new TriangleByIndex[ntri];

	float vx = 0, vy = 1.0f, vz = 0;

	pVerts[0].set(0, 1.0f, 0, 0, 0, 0, 1.0f, 0);

	for (int i = 0; i < vslice; i++)
	{
		for (int j = 0; j <= hslice; j++)
		{
			vx = sinf((float(i + 1) / (vslice + 1)) * ((MATH_2PI) / 2)) * cosf(((float)j / hslice) * MATH_2PI);
			vy = cosf((float(i + 1) / (vslice + 1)) * ((MATH_2PI) / 2));
			vz = sinf((float(i + 1) / (vslice + 1)) * ((MATH_2PI) / 2)) * sinf(((float)j / hslice) * MATH_2PI);
			pVerts[j + i * (hslice + 1) + 1].set(vx, vy, vz, 0, 0, vx, vy, vz);
		}
		pVerts[nverts - 1].set(0, -1.0f, 0, 0, 0, 0, 0, -1.0f, 0);
	}
	int n = 0;
	for (int h = 0; h < hslice; h++)
	{
		pTriList[n++].set(0, h + 2, h + 1);

		for (int v = 0; v < vslice - 1; v++)
		{
			pTriList[n++].set(
				(hslice + 1) * v + h + 1,
				(hslice + 1) * v + h + 2,
				(hslice + 1) * v + h + 3 + hslice
			);
			pTriList[n++].set(
				(hslice + 1) * v + h + 1,
				(hslice + 1) * v + h + 3 + hslice,
				(hslice + 1) * v + h + 2 + hslice
			);
		}
	}

	for (int i = 1; i <= hslice; i++) pTriList[n++].set(nverts - 1, nverts - i - 2, nverts - i - 1);
}

void ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f); // 1,0
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.75f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.625f);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625f);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75f, 0.625f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

