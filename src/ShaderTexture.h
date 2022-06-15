#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(const ShaderTexture&) = delete;
	ShaderTexture(ShaderTexture&&) = default;
	ShaderTexture& operator=(const ShaderTexture&) & = default;
	ShaderTexture& operator=(ShaderTexture&&) & = default;
	~ShaderTexture();

	ShaderTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderTexture::SendWorld(const Matrix& world);

private:
	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_World
	{
		Matrix World;
	};

	ID3D11Buffer* mpBuffWorld;
};

#endif _ShaderTexture
