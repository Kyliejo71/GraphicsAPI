#include "GraphicObject_Texture.h"
#include "Model.h"
#include "Texture.h"

GraphicObject_Texture::~GraphicObject_Texture()
{
}

void GraphicObject_Texture::SetTexture(Texture* ptex)
{
	pTexture = ptex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::Render()
{
	pShader->SetTextureResourceAndSampler(pTexture);
	pShader->SendWorld(World);
	pModel->SetToContext(pShader->GetContext());
	pModel->Render(pShader->GetContext());
}

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	World = Matrix(IDENTITY);
}
