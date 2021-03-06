﻿#include "ClickEffect.h"

namespace gameframework
{
	ClickEffect::ClickEffect()
	{
		m_partScheduler.Register(new ScalingFadeInOutSquare(_T("Texture/キラ十字円.png"), 45, 2.0f, Color(0xFF2323FF), Color(0xFF23FF88)));
		m_partScheduler.Register(new ScalingFadeInOutSquare(_T("Texture/中空き円.png"), 20, 4.0f, Color(0xFF662323), Color(0xFF68FF23)));
		m_partScheduler.Register(new ScalingFadeInOutSquare(_T("Texture/中空き円.png"), 30, 2.5f, Color(0xFF2323FF), Color(0xFF23FF88)));

		for (int i = 7; i > 0; --i)
		{
			m_partScheduler.Register(new DiffuseDifferenceSquare(_T("Texture/キラ.png"), 1.0f, 0.13f, rand() % 20, Color(0xFF23FFFF), Color(0xFFFF23FF)));
		}
	}

	ClickEffect::~ClickEffect()
	{

	}

	void ClickEffect::Update()
	{
		UpdateParts();

		if (!m_partScheduler.IsEnd()) return;
		
		m_isEnd = true;
	}
}
