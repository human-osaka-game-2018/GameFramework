#ifndef FOLLOW_UP_CURSOR_EFFECT_H
#define FOLLOW_UP_CURSOR_EFFECT_H

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
	/// カーソル追従正方形
	/// </summary>
	class FollowUpCursorSquare :public Part
	{
	public:
		/// <param name="pTexturePath">テクスチャのパス</param>
		/// <param name="size">サイズ</param>
		FollowUpCursorSquare(const TCHAR* pTexturePath, float size);

		~FollowUpCursorSquare();

		/// <summary>
		/// 矩形を変形させたりする
		/// </summary>
		virtual void Update()override;

	protected:
		FollowUpCursorSquare(const FollowUpCursorSquare& scalingFadeInOutCircle) = delete;

		FollowUpCursorSquare& operator=(const FollowUpCursorSquare& scalingFadeInOutCircle) = delete;
	};
}

#endif //!FOLLOW_UP_CURSOR_EFFECT_H
