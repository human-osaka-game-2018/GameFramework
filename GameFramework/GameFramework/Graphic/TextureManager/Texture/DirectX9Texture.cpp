#include "DirectX9Texture.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9Texture::Reset(const TCHAR* pTexturePath)
	{
		Release();

		LPDIRECT3DDEVICE pDirectXGraphicDevice = nullptr;
		DirectXParam::GetDirectXGraphicDevice()->Get(&pDirectXGraphicDevice);

		D3DXCreateTextureFromFile(
			pDirectXGraphicDevice,
			pTexturePath,
			&m_pTexture);

		D3DSURFACE_DESC desc;
		m_pTexture->GetLevelDesc(0, &desc);

		m_textureSize.m_width  = static_cast<float>(desc.Width);
		m_textureSize.m_height = static_cast<float>(desc.Height);
	}

	#endif //DIRECT_X_VERSOIN_9
}
