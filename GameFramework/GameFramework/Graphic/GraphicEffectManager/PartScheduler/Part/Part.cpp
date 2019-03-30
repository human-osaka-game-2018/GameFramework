#include "Part.h"

namespace gameframework
{
	ColorBlender* Part::m_pColorBlender = nullptr;
	TextureManager* Part::m_pTextureManager = nullptr;

	Part::~Part()
	{
		Finalize();
	}

	void Part::SetGraphicHelper(ColorBlender* pColorBlender, TextureManager* pTextureManager)
	{
		m_pColorBlender = pColorBlender;
		m_pTextureManager = pTextureManager;
	}

	void Part::Render(bool isAdditionBlendMode)
	{
		if (isAdditionBlendMode) m_pColorBlender->ToAddtionBlendMode();

		m_pVertices->Render(m_pTextureManager->Get(TEXTURE_KEY));
		
		m_pColorBlender->ToDefaultBlendMode();
	}

	void Part::LoadResource()
	{
		m_pTextureManager->Create(TEXTURE_KEY, TEXTURE_KEY);
	}

	Part::Part(const TCHAR* pTexturePath) :TEXTURE_KEY(pTexturePath)
	{
		Initialize();
	}

	void Part::Initialize()
	{
		GameFrameworkFactory::Create(&m_pVertices);
		LoadResource();
	}

	void Part::Finalize()
	{
		Release();
	}

	void Part::Release()
	{
		delete m_pVertices;
	}

	void Part::UpdateVertices()
	{
		if (m_isEnd) return;

		m_behaviorScheduler.Update(m_pVertices);

		++m_lifeFrame;
	}
}
