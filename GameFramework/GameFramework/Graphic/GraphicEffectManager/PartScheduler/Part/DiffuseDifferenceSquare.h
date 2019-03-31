#ifndef DIFFUSE_DIFFERENCE_SQUARE_H
#define DIFFUSE_DIFFERENCE_SQUARE_H

#include <tchar.h>

#include "Part.h"
#include "Vertices.h"
#include "Texture/Texture.h"
#include "TextureManager.h"
#include "ColorBlender/ColorBlender.h"
#include "GameFrameworkFactory.h"
#include "Behavior/Behavior.h"
#include "BehaviorScheduler.h"
#include "Behavior/FollowUpCursor.h"
#include "Behavior/Scaling.h"
#include "Behavior/Flash.h"
#include "Behavior/RotationZ.h"
#include "Behavior/ColorChange.h"
#include "SizeDifferenceSquare.h"
#include "Behavior/Diffuse.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 点滅色遷移拡散する誤差あり正方形
	/// </summary>
	/// <remarks>
	/// 合計三回点滅しその後消える
	/// </remarks>
	class DiffuseDifferenceSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="diffuseAmount">拡散量</param>
		/// <param name="scalingAmount">拡大量</param>
		/// <param name="startDelayFrame">何フレーム後に出現しだすか</param>
		DiffuseDifferenceSquare(const TCHAR* pTexturePath, float diffuseAmount, float scalingAmount, int startDelayFrame, Color originalColor, Color destColor);

		~DiffuseDifferenceSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

		virtual void Render(bool isAdditionBlendMode)override;

	protected:
		DiffuseDifferenceSquare(const DiffuseDifferenceSquare& scalingFadeInOutCircle) = delete;

		DiffuseDifferenceSquare& operator=(const DiffuseDifferenceSquare& scalingFadeInOutCircle) = delete;

		const int FLASH_COUNT_MAX = 15;
		const int LIFE_LIMIT = 3 * FLASH_COUNT_MAX;
		int m_startDelayFrame = 0;
	};
}

#endif //!DIFFUSE_DIFFERENCE_SQUARE_H
