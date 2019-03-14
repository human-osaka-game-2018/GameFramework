#include "DirectX9Stream.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9Stream::Render(const LPFONT pFont, UINT format)
	{
		RECT rect;
		SetRectEmpty(&rect);

		//ここでは矩形を作成しているだけで描画はしていない
		pFont->DrawText(NULL, c_str(), -1, &rect, format | DT_CALCRECT, 0xFFFFFFFF);

		OffsetRect(&rect, static_cast<int>(m_topLeft.x), static_cast<int>(m_topLeft.y));

		pFont->DrawText(NULL, c_str(), -1, &rect, format, m_color.GetColorCode());
	}

	#endif //DIRECT_X_VERSOIN_9
}
