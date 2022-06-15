#include "SkyBoxTool.h"
#include "Matrix.h"
#include <assert.h>
#include "SkyBox.h"
#include "d3dUtil.h"
#include "Model.h"

void SkyBoxTool::CreateSkyBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri, float size)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(size * 1.0f, size * 1.0f, size * 1.0f, 0.5f, 0.333f); // 1
	pVerts[vind + 1].set(size * -1.0f, size * 1.0f, size * 1.0f, 0.25f, 0.333f); //2
	pVerts[vind + 2].set(size * -1.0f, size * -1.0f, size * 1.0f, 0.25f, 0.666f); //3
	pVerts[vind + 3].set(size * 1.0f, size * -1.0f, size * 1.0f, 0.5f, 0.666f); //4
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(size * -1.0f, size * 1.0f, size * -1.0f, 1.0f, 0.333f); // 6
	pVerts[vind + 1].set(size * 1.0f, size * 1.0f, size * -1.0f, 0.75f, 0.333f); //5
	pVerts[vind + 2].set(size * 1.0f, size * -1.0f, size * -1.0f, 0.75f, 0.666f); // 7
	pVerts[vind + 3].set(size * -1.0f, size * -1.0f, size * -1.0f, 1.0f, 0.666f); //8
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(size * -1.0f, size * 1.0f, size * 1.0f, 0.25f, 0.333f); // 2
	pVerts[vind + 1].set(size * -1.0f, size * 1.0f, size * -1.0f, 0.0f, 0.333f); //6
	pVerts[vind + 2].set(size * -1.0f, size * -1.0f, size * -1.0f, 0.0f, 0.666f); //8
	pVerts[vind + 3].set(size * -1.0f, size * -1.0f, size * 1.0f, 0.25f, 0.666f); //3
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(size * 1.0f, size * 1.0f, size * -1.0f, 0.75f, 0.333f); //5
	pVerts[vind + 1].set(size * 1.0f, size * 1.0f, size * 1.0f, 0.5f, 0.333f); //1
	pVerts[vind + 2].set(size * 1.0f, size * -1.0f, size * 1.0f, 0.5f, 0.666f); //4
	pVerts[vind + 3].set(size * 1.0f, size * -1.0f, size * -1.0f, 0.75f, 0.666f); //7
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(size * 1.0f, size * 1.0f, size * -1.0f, 0.5f, 0.0f); // 5
	pVerts[vind + 1].set(size * -1.0f, size * 1.0f, size * -1.0f, 0.25f, 0.0f); //6
	pVerts[vind + 2].set(size * -1.0f, size * 1.0f, size * 1.0f, 0.25f, 0.333f); //2
	pVerts[vind + 3].set(size * 1.0f, size * 1.0f, size * 1.0f, 0.5f, 0.333f); // 1
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(size * 1.0f, size * -1.0f, size * 1.0f, 0.5f, 0.666f);// 4
	pVerts[vind + 1].set(size * -1.0f, size * -1.0f, size * 1.0f, 0.25f, 0.666f); //3
	pVerts[vind + 2].set(size * -1.0f, size * -1.0f, size * -1.0f, 0.25f, 1.0f); // 8
	pVerts[vind + 3].set(size * 1.0f, size * -1.0f, size * -1.0f, 0.5f, 1.0f); //7
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);
}
