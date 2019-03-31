#include "GraphicEffect.h"

namespace gameframework
{
	GraphicEffect::~GraphicEffect()
	{

	}

	void GraphicEffect::Render()
	{
		m_partScheduler.Render(m_isAdditionBlendMode);
	}

	GraphicEffect::GraphicEffect(bool isAdditonBlendMode) :m_isAdditionBlendMode(isAdditonBlendMode)
	{

	}

	void GraphicEffect::UpdateParts()
	{
		m_partScheduler.Update();

		++m_lifeFrame;
	}
}
