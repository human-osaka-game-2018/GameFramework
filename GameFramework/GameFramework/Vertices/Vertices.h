#ifndef VERTICES_H
#define VERTICES_H

#include <vector>

#include <d3dx9.h>

#include "RectSize.h"
#include "Color.h"
#include "TextureUVs.h"
#include "Degree.h"
#include "algorithm.h"
#include "Texture/Texture.h"
#include "DirectXGraphicDevice/DirectXGraphicDevice.h"
#include "DirectXParam.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	/// <summary>
	/// DirectX9での頂点構造体
	/// </summary>
	struct CustomVertex
	{
	public:
		D3DXVECTOR3 m_pos;

		/// <summary>
		/// 重みの逆数 基本1
		/// </summary>
		float m_rHW = 1.0f;

		DWORD m_aRGB = 0xFFFFFFFF;

		D3DXVECTOR2 m_texUV;

		static const int RECT_VERTICES_NUM = 4;
	};
	#elif defined DIRECT_X_VERSOIN_9
	/// <summary>
	/// DirectX9での頂点構造体
	/// </summary>
	struct CustomVertex
	{
	public:
		D3DXVECTOR3 m_pos;

		/// <summary>
		/// 重みの逆数 基本1
		/// </summary>
		float m_rHW = 1.0f;

		DWORD m_aRGB = 0xFFFFFFFF;

		D3DXVECTOR2 m_texUV;

		static const int RECT_VERTICES_NUM = 4;
	};
	#else
	#error "DirectXのバージョンを定義してください"
	#endif

	class Vertices
	{
	public:
		Vertices() 
		{
			DirectXParam::GetDirectXGraphicDevice()->Get(&m_pDirectXGraphicDevice);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& size)
		{
			SetCenterAndSize(center, size);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
		{
			SetCenterAndSizeAndColor(center, size, color);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs)
		{
			SetCenterAndSizeAndColorAndTextureUVs(center, size, color, textureUVs);
		}

		Vertices(const D3DXVECTOR3& center, const RectSize& size, const Color& color, const TextureUVs& textureUVs,
			const Degree& rotationX_deg, const Degree& rotationY_deg, const Degree& rotationZ_deg)
		{
			SetCenterAndSizeAndColorAndTextureUVs(center, size, color, textureUVs);

			SetRotationX(rotationX_deg);
			SetRotationY(rotationY_deg);
			SetRotationZ(rotationZ_deg);
		}

		~Vertices() {};

		/************************************************************************************************************SETTER*/

		inline void SetCenter(const D3DXVECTOR3& center)
		{
			m_center = center;
		}

		inline void SetHalfScale(const RectSize& halfScale)
		inline void Setsize(const RectSize& size)
		{
			m_baseSize = size;
		}

		inline void SetColor(const Color& color)
		{
			m_color = color;
		}

		inline void SetTextureUVs(const TextureUVs& textureUVs)
		{
			m_textureUVs = textureUVs;
		}

		inline void SetRotationX(const Degree& rotationX_deg)
		{
			m_rotationX_deg = rotationX_deg;
		}

		inline void SetRotationY(const Degree& rotationY_deg)
		{
			m_rotationY_deg = rotationY_deg;
		}

		inline void SetRotationZ(const Degree& rotationZ_deg)
		{
			m_rotationZ_deg = rotationZ_deg;
		}

		inline void SetCenterAndSize(const D3DXVECTOR3& center, const RectSize& size)
		{
			SetCenter(center);
			Setsize(size);
		}

		inline void SetCenterAndSizeAndColor(const D3DXVECTOR3& center, const RectSize& size, const Color& color)
		{
			SetCenterAndSize(center, size);
			SetColor(color);
		}

		inline void SetCenterAndSizeAndColorAndTextureUVs(const D3DXVECTOR3& center, const RectSize& size, const Color& color, 
			const TextureUVs& textureUVs)
		{
			SetCenterAndSizeAndColor(center, size, color);
			SetTextureUVs(textureUVs);
		}

		/************************************************************************************************************GETTER*/

		inline D3DXVECTOR3& GetCenter()
		{
			return	m_center;
		}

		inline RectSize& Getsize()
		{
			return m_baseSize;
		}

		inline Color& GetColor()
		{
			return m_color;
		}

		inline TextureUVs& GetTextureUVs()
		{
			return m_textureUVs;
		}

		/// <summary>
		/// 矩形を点滅させる
		/// </summary>
		/// <param name="flashFrameMax">点滅にかかるカウント数</param>
		/// <param name="alphaMin">点滅のアルファ値の最大値</param>
		/// <param name="alphaMax">点滅のアルファ値の最小値</param>
		inline void Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax)
		{
			m_color.m_alpha = static_cast<BYTE>(algorithm::SwitchMinBetweenMax(m_flashFrameCount, flashFrameMax, alphaMin, alphaMax));
			algorithm::CountUp(&m_flashFrameCount, flashFrameMax);
		}
		
		/// <summary>
		/// 矩形を拡縮させる
		/// </summary>
		/// <param name="scalingFrameMax">拡縮にかかるカウント数</param>
		/// <param name="scaleRateMin">拡縮の最大倍率</param>
		/// <param name="scaleRateMax">拡縮の最小倍率</param>
		inline void Scaling(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
		{
			float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
			algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

			m_sizeForRender = m_baseSize * scaleRate;

			m_hasUpdatedSize = true;
		}

		/// <summary>
		/// widthのみ拡縮
		/// </summary>
		inline void ScalingX(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
		{
			float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
			algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

			m_sizeForRender.m_width = m_baseSize.m_width * scaleRate;

			m_hasUpdatedSize = true;
		}

		/// <summary>
		/// heightのみ拡縮
		/// </summary>
		inline void ScalingY(int scalingFrameMax, float scaleRateMin, float scaleRateMax)
		{
			float scaleRate = algorithm::SwitchMinBetweenMax(m_additionalScaleFrameCount, scalingFrameMax, scaleRateMin, scaleRateMax);
			algorithm::CountUp(&m_additionalScaleFrameCount, scalingFrameMax);

			m_sizeForRender.m_height = m_baseSize.m_height * scaleRate;

			m_hasUpdatedSize = true;
		}

		inline void AddRotationX(const Degree& rotationX_deg)
		{
			m_rotationX_deg += rotationX_deg;
		}

		inline void AddRotationY(const Degree& rotationY_deg)
		{
			m_rotationY_deg += rotationY_deg;
		}

		inline void AddRotationZ(const Degree& rotationZ_deg)
		{
			m_rotationZ_deg += rotationZ_deg;
		}
		
		/// <summary>
		/// 描画を行う
		/// </summary>
		/// <param name="pTexture">描画する際に扱うテクスチャ</param>
		virtual void Render(const LPTEXTURE pTexture) = 0;

	protected:
		/// <summary>
		/// 描画を行う際の矩形を作成する
		/// </summary>
		virtual void Normalize() = 0;

		D3DXVECTOR3 m_center = { 0.0f, 0.0f, 0.0f };
		RectSize m_baseSize;
		RectSize m_sizeForRender;
		Color m_color;
		TextureUVs m_textureUVs;
		Degree m_rotationX_deg;
		Degree m_rotationY_deg;
		Degree m_rotationZ_deg;
		int m_flashFrameCount = 0;
		int m_additionalScaleFrameCount = 0;
		bool m_hasUpdatedSize = false;
		
		/// <summary>
		/// 矩形の頂点分のサイズ
		/// </summary>
		CustomVertex m_vertices[4];

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;
	};
}

#endif //!VERTICES_H
