#ifndef _SkyBoxTool
#define _SkyBoxTool

#include "Vect.h"

struct StandardVertex;
struct TriangleByIndex;

class SkyBoxTool
{

public:
	static void CreateSkyBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri, float size);
};



#endif _SkyBoxTool