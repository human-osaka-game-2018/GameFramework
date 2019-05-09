#include "DiffuseDifferenceSquare.h"

namespace gameframework
{
	DiffuseDifferenceSquare::DiffuseDifferenceSquare(const TCHAR* pTexturePath,
		float diffuseAmount, float scalingAmount, int startDelayFrame, Color originalColor, Color destColor)
		:Part(pTexturePath), m_startDelayFrame(startDelayFrame)
	{
		m_behaviorScheduler.Register(new FollowUpCursor(), BehaviorData::DEFAULT_START, 0, 1);

		Prepare(diffuseAmount, scalingAmount, originalColor, destColor);
	}

	DiffuseDifferenceSquare::DiffuseDifferenceSquare(const TCHAR* pTexturePath,
		float diffuseAmount, float scalingAmount, int startDelayFrame, Color originalColor, Color destColor, const D3DXVECTOR3& occurencePos)
		:Part(pTexturePath), m_startDelayFrame(startDelayFrame)
	{
		m_behaviorScheduler.Register(new Locale(occurencePos), BehaviorData::DEFAULT_START, 0, 1);

		Prepare(diffuseAmount, scalingAmount, originalColor, destColor);
	}

	DiffuseDifferenceSquare::~DiffuseDifferenceSquare()
	{

	}

	void DiffuseDifferenceSquare::Update()
	{
		if (m_isEnd) return;

		UpdateVertices();

		if ((m_startDelayFrame--) > 0) return;

		if (m_lifeFrame >= LIFE_LIMIT)
		{
			m_isEnd = true;
		}
	}

	void DiffuseDifferenceSquare::Render(bool isAdditionBlendMode)
	{
		if (m_isEnd) return;

		if (m_startDelayFrame + 1 > 0) return;

		if (isAdditionBlendMode) m_pColorBlender->ToAddtionBlendMode();

		m_pVertices->Render(m_pTextureManager->Get(TEXTURE_KEY));

		m_pColorBlender->ToDefaultBlendMode();
	}

	void DiffuseDifferenceSquare::Prepare(float diffuseAmount, float scalingAmount, Color originalColor, Color destColor)
	{
		m_lifeFrame -= m_startDelayFrame;

		SizeDifferenceSquare SizeDifferenceSquare(3.0f, 10.0f);
		SizeDifferenceSquare.ShapeVertices(m_pVertices);

		m_behaviorScheduler.Register(new Diffuse(diffuseAmount, 0.0f, 360.0f), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Scaling(scalingAmount), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new ColorChange(LIFE_LIMIT, originalColor, destColor), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
		m_behaviorScheduler.Register(new Flash(FLASH_COUNT_MAX, 0, 255), BehaviorData::DEFAULT_START, m_startDelayFrame, BehaviorData::UNLIMITED);
	}
}
