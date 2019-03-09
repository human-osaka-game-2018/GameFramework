//----------------------------------------------------------
// <filename>GameFrameworkFactory.h</filename>
//----------------------------------------------------------

#ifndef GAME_FRAMEWORK_FACTORY_H
#define GAME_FRAMEWORK_FACTORY_H

#include "DirectXDevice/DirectXDevice.h"
#include "DirectXDevice/DirectX9Device.h"
#include "DirectXGraphicDevice/DirectXGraphicDevice.h"
#include "DirectXGraphicDevice/DirectX9GraphicDevice.h"
#include "DirectXInputDevice/DirectXInputDevice.h"
#include "DirectXInputDevice/DirectX8InputDevice.h"

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	class GameFrameFactory
	{
	public:
		template<typename T>
		static void Create(T** ppT)
		{
			pT = new T();
		}

		template<>
		static void Create<DirectXDevice>(DirectXDevice** ppDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			*ppDirectXDevice = nullptr;
			#else
			*ppDirectXDevice = new DirectX9Device();
			#endif
		}

		static void Create(DirectXGraphicDevice** ppDirectXGraphicDevice, DirectXDevice* pDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			ppDirectXDevice = nullptr;
			#else
			*ppDirectXGraphicDevice = new DirectX9GraphicDevice(pDirectXDevice);
			#endif
		}

		template<>
		static void Create<DirectXInputDevice>(DirectXInputDevice** ppDirectXInputDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			pDirectXInputDevice = nullptr;
			#else
			*ppDirectXInputDevice = new DirectX8InputDevice();
			#endif
		}

	private:
		GameFrameFactory() {};
		GameFrameFactory(const GameFrameFactory& rhs) = delete;

		~GameFrameFactory() {};

		GameFrameFactory& operator=(const GameFrameFactory& rhs) = delete;
	};
}

#endif //! GAME_FRAMEWORK_FACTORY_H
