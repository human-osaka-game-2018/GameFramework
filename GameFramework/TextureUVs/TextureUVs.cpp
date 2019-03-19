#include "TextureUVs.h"

#include "Algorithm.h"

namespace gameframework
{
	TextureUVs::TextureUVs()
	{
		ResizeTextureUVsForRect();
	}

	TextureUVs::TextureUVs(const D3DXVECTOR2& topLeft, const RectSize& textureSize, const RectSize& oneDivideSize, int dividesNumMax)
	{
		ResizeTextureUVsForRect();
		SetTextureUVsParams(topLeft, textureSize, oneDivideSize, dividesNumMax);
	}

	TextureUVs::~TextureUVs()
	{

	}

	void TextureUVs::Next()
	{
		//アニメーションの最大枚数を超えていたら
		if (m_currentDivideNum >= m_dividesNumMax)
		{
			m_topLeft = { 0.0f, 0.0f };

			m_currentDivideNum = 1;

			return;
		}

		++m_currentDivideNum;

		//統合ファイルの一区切り分右にずらす
		m_topLeft.x += m_oneDivideSize.m_width;

		//右にずらしたときにテクスチャ座標tuが1.0fを超えていなければok
		if (m_topLeft.x + m_oneDivideSize.m_width <= m_textureSize.m_width) return;

		//1.0fを超えていたら統合ファイルの一番左にずらし行を次に進める
		m_topLeft.x = 0.0f;
		m_topLeft.y += m_oneDivideSize.m_height;

		//下にずらしたときテクスチャ座標tvが1.0fを超えていなければok
		if (m_topLeft.y + m_oneDivideSize.m_height <= m_textureSize.m_height) return;

		//超えていれば初期値に戻る
		m_topLeft.y = 0.0f;
	}

	void TextureUVs::Normalize()
	{
		for (auto& textureUV : m_textureUVs)
		{
			int index = static_cast<int>(&textureUV - &m_textureUVs[0]);

			textureUV =
			{
				(m_topLeft.x + algorithm::Tertiary(IsRightSide(index), m_oneDivideSize.m_width,  0.0f)) / m_textureSize.m_width,
				(m_topLeft.y + algorithm::Tertiary(IsUnderSide(index), m_oneDivideSize.m_height, 0.0f)) / m_textureSize.m_height
			};
		}
	}

	void TextureUVs::ResizeTextureUVsForRect()
	{
		//矩形の頂点数分確保するこれ以上は増やさないし減らさない
		m_textureUVs.resize(4);
	}
}
