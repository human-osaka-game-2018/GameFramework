#include "ColorChange.h"

namespace gameframework
{
	const std::vector<Color::COMPONENT> ColorChange::COLOR_COMPONENTS =
	{
		Color::COMPONENT::ALPHA,
		Color::COMPONENT::RED,
		Color::COMPONENT::GREEN,
		Color::COMPONENT::BLUE
	};

	ColorChange::ColorChange(int changeColorFrame, Color& originalColor, Color& destColor)
		:CHANGE_COLOR_FRAME_MAX(changeColorFrame), m_originalColor(originalColor)
	{
		m_colorComponetAmounts.resize(COLOR_COMPONENTS.size());

		for (auto& COLOR_COMPONENT : COLOR_COMPONENTS)
		{
			int index = static_cast<int>(&COLOR_COMPONENT - &COLOR_COMPONENTS[0]);

			m_colorComponetAmounts[index] = destColor[COLOR_COMPONENT] - originalColor[COLOR_COMPONENT];
		}
	}

	ColorChange::~ColorChange()
	{

	}

	void ColorChange::Impart(Vertices* pVertices)
	{
		//遷移完了のフレームに達していなかったら
		if (m_changeColorFrame < CHANGE_COLOR_FRAME_MAX)
		{
			for (auto& COLOR_COMPONENT : COLOR_COMPONENTS)
			{
				int index = static_cast<int>(&COLOR_COMPONENT - &COLOR_COMPONENTS[0]);

				pVertices->GetColor()[COLOR_COMPONENT] = m_originalColor[COLOR_COMPONENT] +
					static_cast<int>(m_colorComponetAmounts[index] * (static_cast<float>(m_changeColorFrame) / CHANGE_COLOR_FRAME_MAX));
			}

			++m_changeColorFrame;

			return;
		}

		m_isEnd = true;
	}
}
