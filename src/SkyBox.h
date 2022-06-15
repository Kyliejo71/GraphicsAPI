#ifndef _SkyBox
#define _SkyBox

#include <d3d11.h>
#include "Vect.h"
#include "Align16.h"
#include "Matrix.h"
#include "Model.h"

class SkyBox
{
private:
	// Model information
	TriangleByIndex* pTriList;
	StandardVertex* pStdVerts;
	int numVerts;
	int numTris;
	float sizeOfBox;

	// GPU connections
	ID3D11Device* mDevice;
	ID3D11Buffer* mpVertexBuffer;
	ID3D11Buffer* mpIndexBuffer;

	void privLoadDataToGPU();

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(SkyBox&&) = delete;                    // Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator

	SkyBox(ID3D11Device* dev, float size);

	virtual ~SkyBox();

	void SetToContext(ID3D11DeviceContext* context);
	void Render(ID3D11DeviceContext* context);
};



#endif _SkyBox

