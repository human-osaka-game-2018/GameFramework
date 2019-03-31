#include "FollowUpCursor.h"

namespace gameframework
{
	FollowUpCursor::FollowUpCursor()
	{

	}

	FollowUpCursor::~FollowUpCursor()
	{

	}

	void FollowUpCursor::Impart(Vertices* pVertices)
	{
		GetPos(&pVertices->GetCenter());
		++m_lifeFrame;
	}

	void FollowUpCursor::GetPos(D3DXVECTOR3* pCursorPos)
	{
		POINT cursorPoint;

		//ここではまだディスプレイ基準の絶対座標
		GetCursorPos(&cursorPoint);

		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		//ここでウィンドウ基準の相対座標に変換
		ScreenToClient(hWnd, &cursorPoint);

		m_baseCenter = { static_cast<float>(cursorPoint.x), static_cast<float>(cursorPoint.y), 0.0f };
		*pCursorPos = m_baseCenter;
	}
}
