#include "DirectX9Vertices.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	DirectX9Vertices::DirectX9Vertices() {};

	DirectX9Vertices::DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size) :Vertices(center, size)	{};

	DirectX9Vertices::DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
		: Vertices(center, size, color) {};

	DirectX9Vertices::DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs)
		: Vertices(center, size, color, textureUVs) {};

	DirectX9Vertices::DirectX9Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs,
		const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg)
		: Vertices(center, size, color, textureUVs, rotationX_deg, rotationY_deg, rotationZ_deg) {};

	DirectX9Vertices::~DirectX9Vertices() {};

	void DirectX9Vertices::CreateCustomVertices()
	{
		//Renderでフラグをニュートラルにする
		if (!m_hasUpdatedSize)
		{
			m_sizeForRender = m_baseSize;
		}
		
		m_vertices.Reset(m_center, m_sizeForRender, m_color, m_textureUVs);
		m_vertices.RotateXYZ(m_rotationX_deg, m_rotationY_deg, m_rotationZ_deg);
	}

	void DirectX9Vertices::Render(const LPTEXTURE pTexture)
	{
		m_pDirectXGraphicDevice->SetFVF(
			D3DFVF_XYZRHW |
			D3DFVF_DIFFUSE |
			D3DFVF_TEX1);

		m_pDirectXGraphicDevice->SetTexture(0, pTexture);

		CreateCustomVertices();
		m_hasUpdatedSize = false;

		m_pDirectXGraphicDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			m_vertices.Get(),
			sizeof(CustomVertex));
	}

	#endif //DIRECT_X_VERSOIN_9
}
