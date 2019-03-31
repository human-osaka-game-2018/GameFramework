#include "ScalingFadeInOutSquare.h"

namespace gameframework
{
	ScalingFadeInOutSquare::ScalingFadeInOutSquare(const TCHAR* pTexturePath, int lifeFrameMax, float scalingAmount, Color originColor, Color destColor)
		:Part(pTexturePath), LIFE_FRAME_MAX(lifeFrameMax)
	{
		SizeDifferenceSquare SizeDifferenceSquare(0.0f, 0.0f);
		SizeDifferenceSquare.ShapeVertices(m_pVertices);

		m_behaviorScheduler.Register(new FollowUpCursor(), BehaviorData::DEFAULT_START, 0, 1);
		m_behaviorScheduler.Register(new Scaling(scalingAmount), BehaviorData::DEFAULT_START, 0, LIFE_FRAME_MAX);
		m_behaviorScheduler.Register(new ColorChange(LIFE_FRAME_MAX, originColor, destColor), BehaviorData::DEFAULT_START, 0, LIFE_FRAME_MAX);
		m_behaviorScheduler.Register(new Flash(LIFE_FRAME_MAX, 0, 255), BehaviorData::DEFAULT_START, 0, LIFE_FRAME_MAX);
		m_behaviorScheduler.Register(new RotationZ(6.0f), BehaviorData::DEFAULT_START, 0, LIFE_FRAME_MAX);
	}

	ScalingFadeInOutSquare::~ScalingFadeInOutSquare()
	{

	}

	void ScalingFadeInOutSquare::Update()
	{
		UpdateVertices();

		if (m_lifeFrame >= LIFE_FRAME_MAX)
		{
			m_isEnd = true;
		}
	}
}
