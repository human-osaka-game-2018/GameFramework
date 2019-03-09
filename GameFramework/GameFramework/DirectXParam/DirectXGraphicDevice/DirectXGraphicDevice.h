//----------------------------------------------------------
// <filename>DirectXGraphicDevice.h</filename>
//----------------------------------------------------------

#ifndef DIRECT_X_GRAPHIC_DEVICE_H
#define DIRECT_X_GRAPHIC_DEVICE_H

#include <Windows.h>

#include <d3dx9.h>

#include "DirectXDevice/DirectXDevice.h"

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace BaseFramework
{
	#ifdef DIRECT_X_VERSION_11
	//using LPDIRECT3DDEVICE = LPDIRECT3DDEVICE9;
	#else
	using LPDIRECT3DDEVICE = LPDIRECT3DDEVICE9;
	#endif //! DIRECT_X_VERSION_11
		
	/// <summary>
	/// DirectXのグラフィックデバイスクラス
	/// </summary>
	class DirectXGraphicDevice
	{
	public:
		DirectXGraphicDevice() {};

		virtual ~DirectXGraphicDevice()
		{
			m_pDirectXGraphicDevice->Release();
			delete m_pDirectXGraphicDevice;
		}

		inline void Get(LPDIRECT3DDEVICE* ppDirectXDevice) const
		{
			*ppDirectXDevice = m_pDirectXGraphicDevice;
		}

	protected:
		/// <summary>
		/// DirectXのグラフィックデバイスを作成する
		/// </summary>
		/// <param name="pDirectXDevice">DirectXのデバイスクラスのポインタ</param>
		virtual void Create(DirectXDevice* pDirectXDevice) = 0;

		LPDIRECT3DDEVICE m_pDirectXGraphicDevice = nullptr;

	private:
		DirectXGraphicDevice(const DirectXGraphicDevice& rhs) = delete;

		DirectXGraphicDevice& operator=(const DirectXGraphicDevice& rhs) = delete;
	};
}

#endif //! DIRECT_X_GRAPHIC_DEVICE_H
