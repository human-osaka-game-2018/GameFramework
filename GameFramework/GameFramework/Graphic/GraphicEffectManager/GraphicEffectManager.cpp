#include "GraphicEffectManager.h"

namespace gameframework
{
	GraphicEffectManager::GraphicEffectManager()
	{

	}

	GraphicEffectManager::~GraphicEffectManager()
	{

	}

	void GraphicEffectManager::Register(GraphicEffect* pGraphicEffect)
	{
		m_pGraphicEffects.push_back(pGraphicEffect);
	}

	void GraphicEffectManager::ReleaseAll()
	{
		for (auto effect : m_pGraphicEffects)
		{
			delete effect;
		}

		if (m_pGraphicEffects.size() == 0) return;

		m_pGraphicEffects.clear();
		m_pGraphicEffects.shrink_to_fit();
	}

	void GraphicEffectManager::Update()
	{
		ReleaseEndEffect();

		for (auto effect : m_pGraphicEffects)
		{
			effect->Update();
		}
	}

	void GraphicEffectManager::Render()
	{
		for (auto effect : m_pGraphicEffects)
		{
			effect->Render();
		}
	}

	void GraphicEffectManager::ReleaseEndEffect()
	{
		bool isReleased = false;

		for (int i = static_cast<int>(m_pGraphicEffects.size() - 1); i >= 0; --i)
		{
			if (!m_pGraphicEffects[i]->IsEnd()) continue;

			delete m_pGraphicEffects[i];

			// 現在のiが指し示している場所の削除
			m_pGraphicEffects.erase(m_pGraphicEffects.begin() + i);

			isReleased = true;
		}

		if (!isReleased) return;

		m_pGraphicEffects.shrink_to_fit();
	}
}
