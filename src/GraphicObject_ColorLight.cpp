#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);
	int n = mod->GetMeshCount();
	Ambient = new Vect[n];
	Diffuse = new Vect[n];
	Specular = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		Ambient[i] = Vect(0, 0, 0);
		Diffuse[i] = Vect(0, 0, 0);
		Specular[i] = Vect(0, 0, 0);
	}
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] Ambient;
	delete[] Diffuse;
	delete[] Specular;
}

void GraphicObject_ColorLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}
void GraphicObject_ColorLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}
void GraphicObject_ColorLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_ColorLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}
void GraphicObject_ColorLight::SendLightParameters(const Vect& eyepos)
{
	pShader->SendLightParameters(eyepos);
}
void GraphicObject_ColorLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshNum)
{

	assert(pModel->ValidMeshNum(meshNum));
	Ambient[meshNum] = amb;
	Diffuse[meshNum] = dif;
	Specular[meshNum] = sp;
}
void GraphicObject_ColorLight::SetWorld(const Matrix& world)
{
	World = world;
}
void GraphicObject_ColorLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{


	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		Ambient[i] = amb;
		Diffuse[i] = dif;
		Specular[i] = sp;
	}

}
void GraphicObject_ColorLight::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}
void GraphicObject_ColorLight::SendFogData(float start, float range, Vect c)
{
	pShader->SendFogData(start, range, c);
}
void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, Ambient[i], Diffuse[i], Specular[i]);

		pModel->RenderMesh(pShader->GetContext(), i);
	}
}