//----------------------------------------------------------
// <filename>DirectX9Font.cpp</filename>
//----------------------------------------------------------

#include "DirectX9Font.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9Font::Reset(const RectSize& scale, const TCHAR* pFontName, UINT thickness)
	{
		m_fontSize = scale;

		Release();

		D3DXCreateFont(
			m_pDirectXGraphicDevice,
			static_cast<int>(scale.m_height), static_cast<int>(scale.m_width),
			thickness,
			0,
			0,
			//日本語を表示するのでキャラセットを固定
			SHIFTJIS_CHARSET,
			0,
			0,
			0,
			pFontName,
			&m_pFont);
	}

	#endif //DIRECT_X_VERSOIN_9
}
