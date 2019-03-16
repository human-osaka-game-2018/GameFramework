#ifndef GAME_FRAMEWORK_FACTORY_H
#define GAME_FRAMEWORK_FACTORY_H

#include "FontManager/Font/Font.h"
#include "FontManager/Font/DirectX9Font.h"
#include "ColorBlender/ColorBlender.h"
#include "ColorBlender/DirectX9ColorBlender.h"
#include "Texture/Texture.h"
#include "Texture/DirectX9Texture.h"
#include "Renderer/Renderer.h"
#include "Renderer/DirectX9Renderer.h"
#include "DirectInput.h"
#include "Direct8Input.h"
#include "Stream.h"
#include "DirectX9Stream.h"
#include "Vertices.h"
#include "DirectX9Vertices.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	class GameFrameworkFactory
	{
	public:
		template<typename T>
		static void Create(T** ppT)
		{
			pT = new T();
		}

		template<>
		static void Create<Font>(Font** ppFont)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppFont = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppFont = new DirectX9Font();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<ColorBlender>(ColorBlender** ppColorBlender)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppColorBlender = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppColorBlender = new DirectX9ColorBlender();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<Renderer>(Renderer** ppRenderer)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppRenderer = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppRenderer = new DirectX9Renderer();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<DirectInput>(DirectInput** ppDirectInput)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppDirectInput = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppDirectInput = new Direct8Input();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<Stream>(Stream** ppStream)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppStream = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppStream = new DirectX9Stream();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		template<>
		static void Create<Vertices>(Vertices** ppVertices)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppVertices = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppVertices = new DirectX9Vertices();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

		static void Create<Texture>(Texture** ppTexture)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppTexture = nullptr;
			#elif defined DIRECT_X_VERSOIN_9
			*ppTexture = new DirectX9Texture();
			#else
			#error "DirectXのバージョンを定義してください"
			#endif
		}

	private:
		GameFrameworkFactory() {};
		GameFrameworkFactory(const GameFrameworkFactory& rhs) = delete;

		~GameFrameworkFactory() {};

		GameFrameworkFactory& operator=(const GameFrameworkFactory& rhs) = delete;
	};
}

#endif //!GAME_FRAMEWORK_FACTORY_H
