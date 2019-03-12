﻿//----------------------------------------------------------
// <filename>DirectX9GraphicDevice.h</filename>
//----------------------------------------------------------

#ifndef DIRECT_X_9_GRAPHIC_DEVICE_H
#define DIRECT_X_9_GRAPHIC_DEVICE_H

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "RectSize.h"
#include "WindowParam/WindowParam.h"
#include "DirectXDevice/DirectXDevice.h"
#include "DirectXGraphicDevice.h"

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifndef DIRECT_X_VERSOIN_11

	/// <summary>
	/// DirectX9のグラフィックデバイスクラス
	/// </summary>
	class DirectX9GraphicDevice :public DirectXGraphicDevice
	{
	public:
		DirectX9GraphicDevice(DirectXDevice* pDirectXDevice)
		{
			Create(pDirectXDevice);
		}

		virtual ~DirectX9GraphicDevice()
		{
			m_pDirectXGraphicDevice->Release();
			delete m_pDirectXGraphicDevice;
		}

	private:
		/// <summary>
		/// DirectXのバックバッファ等の情報をまとめたクラス
		/// </summary>
		class DirectXPresentParam
		{
		public:			
			/// <summary>
			/// ウィンドウモード時のデータを取得
			/// </summary>
			/// <param name="pD3DPRESENT_PARAMETERS">取得した値を入れる構造体のポインタ</param>
			static inline void GetWindowModeParam(D3DPRESENT_PARAMETERS* pD3DPRESENT_PARAMETERS)
			{
				FormatUnionParam(pD3DPRESENT_PARAMETERS);

				pD3DPRESENT_PARAMETERS->Windowed = true;
			}
			
			/// <summary>
			/// フルスクリーンモード時のデータを取得
			/// </summary>
			/// <param name="pD3DPRESENT_PARAMETERS">取得した値を入れる構造体のポインタ</param>
			static inline void GetFullScreenParam(D3DPRESENT_PARAMETERS* pD3DPRESENT_PARAMETERS)
			{
				FormatUnionParam(pD3DPRESENT_PARAMETERS);

				pD3DPRESENT_PARAMETERS->Windowed = false;

				pD3DPRESENT_PARAMETERS->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

				HWND hWnd = nullptr;
				WindowParam::GetWindowHandle(&hWnd);
				pD3DPRESENT_PARAMETERS->hDeviceWindow = hWnd;
			}

		private:
			DirectXPresentParam() {};
			DirectXPresentParam(const DirectXPresentParam& rhs) = delete;

			~DirectXPresentParam() {};

			DirectXPresentParam& operator=(const DirectXPresentParam& rhs) = delete;

			static void FormatUnionParam(D3DPRESENT_PARAMETERS* pD3DPRESENT_PARAMETERS);
		};

		DirectX9GraphicDevice(const DirectX9GraphicDevice& rhs) = delete;

		DirectX9GraphicDevice& operator=(const DirectX9GraphicDevice& rhs) = delete;

		/// <summary>
		/// DirectX9のグラフィックデバイスを作成する
		/// </summary>
		/// <param name="pDirectXDevice">DirectXのデバイスクラスのポインタ</param>
		void Create(DirectXDevice* pDirectXDevice);
	};

	#endif //! DIRECT_X_VERSOIN_11
}

#endif //! DIRECT_X_GRAPHIC_DEVICE_H
