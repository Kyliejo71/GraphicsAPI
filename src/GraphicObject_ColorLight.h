#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
	friend class ShaderColorLight;

public:
	GraphicObject_ColorLight() = delete;
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                  
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;     
	~GraphicObject_ColorLight();	
	
	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

	void SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshnum);
	void SetWorld(const Matrix& world);
	void SetToContext(ID3D11DeviceContext* devcon);
	void SendFogData(float start, float range, Vect c);

	virtual void Render() override;

	GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod);

private:
	ShaderColorLight* pShader;
	Vect* Ambient;
	Vect* Diffuse;
	Vect* Specular;

	Matrix World;

};

#endif _GraphicObject_ColorLight

