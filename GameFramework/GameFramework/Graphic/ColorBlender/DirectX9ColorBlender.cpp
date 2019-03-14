#include "DirectX9ColorBlender.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9ColorBlender::SetDefaultColorBlending() const
	{
		ToDefaultBlendMode();
		m_pDirectXGraphicDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pDirectXGraphicDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDirectXGraphicDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		m_pDirectXGraphicDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

		//アルファ値が0x01以下の部分を描画しない
		m_pDirectXGraphicDevice->SetRenderState(D3DRS_ALPHAREF, 0x01);

		m_pDirectXGraphicDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pDirectXGraphicDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

		m_pDirectXGraphicDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pDirectXGraphicDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	}

	#endif //DIRECT_X_VERSOIN_9
}
