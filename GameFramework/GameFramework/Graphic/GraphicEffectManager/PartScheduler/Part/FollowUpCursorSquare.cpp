#include "FollowUpCursorSquare.h"

namespace gameframework
{
	FollowUpCursorSquare::FollowUpCursorSquare(const TCHAR* pTexturePath, float size)
		:Part(pTexturePath)
	{
		SizeDifferenceSquare SizeDifferenceSquare(size, 0.0f);
		SizeDifferenceSquare.ShapeVertices(m_pVertices);

		m_behaviorScheduler.Register(new FollowUpCursor());
	}

	FollowUpCursorSquare::~FollowUpCursorSquare()
	{

	}

	void FollowUpCursorSquare::Update()
	{
		UpdateVertices();
	}
}
