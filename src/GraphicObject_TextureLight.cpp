#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;
	World = Matrix(IDENTITY);
	int n = mod->GetMeshCount();
	Ambient = new Vect[n];
	Diffuse = new Vect[n];
	Specular = new Vect[n];
	Tex = new Texture * [n];
	for (int i = 0; i < n; i++)
	{
		Ambient[i] = Vect(0, 0, 0);
		Diffuse[i] = Vect(0, 0, 0);
		Specular[i] = Vect(0, 0, 0);
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] Ambient;
	delete[] Diffuse;
	delete[] Specular;
	delete[] Tex;
}
void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
		Tex[i] = tex;
}
void GraphicObject_TextureLight::SetTexture(Texture* tex, const int& meshNum)
{
	assert(pModel->ValidMeshNum(meshNum));
	Tex[meshNum] = tex;
}

void GraphicObject_TextureLight::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetDirectionalLightParameters(dir, amb, dif, sp);
}
void GraphicObject_TextureLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}
void GraphicObject_TextureLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp, int count)
{
	pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp, count);
}

void GraphicObject_TextureLight::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	pShader->SendCamMatrices(view, proj);
}
void GraphicObject_TextureLight::SendLightParameters(const Vect& eyepos)
{
	pShader->SendLightParameters(eyepos);
}
void GraphicObject_TextureLight::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SendWorldAndMaterial(world, amb, dif, sp);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		Ambient[i] = amb;
		Diffuse[i] = dif;
		Specular[i] = sp;

	}

}
void GraphicObject_TextureLight::SetWorld(const Matrix& world)
{
	World = world;
}
void GraphicObject_TextureLight::SendFogData(float start, float range, Vect c)
{
	pShader->SendFogData(start, range, c);
}

void GraphicObject_TextureLight::SetMaterial(const Vect& amb, const Vect& dif, const Vect& sp, const int& meshNum)
{

	assert(pModel->ValidMeshNum(meshNum));
	Ambient[meshNum] = amb;
	Diffuse[meshNum] = dif;
	Specular[meshNum] = sp;

}

void GraphicObject_TextureLight::SetToContext(ID3D11DeviceContext* devcon)
{
	pShader->SetToContext(devcon);
}
void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(Tex[i]);
		pShader->SendWorldAndMaterial(World, Ambient[i], Diffuse[i], Specular[i]);

		pModel->RenderMesh(pShader->GetContext(), i);

	}

}