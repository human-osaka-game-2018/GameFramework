//----------------------------------------------------------
// <filename>GameFrameworkFactory.h</filename>
//----------------------------------------------------------

#ifndef GAME_FRAMEWORK_FACTORY_H
#define GAME_FRAMEWORK_FACTORY_H

#include "DirectXDevice/DirectXDevice.h"
#include "DirectXDevice/DirectX9Device.h"
#include "DirectXGraphicDevice/DirectXGraphicDevice.h"
#include "DirectXGraphicDevice/DirectX9GraphicDevice.h"

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace BaseFramework
{
	class GameFrameFactory
	{
	public:
		template<typename T>
		static void Create(T* pT)
		{
			pT = new T();
		}

		template<>
		static void Create<DirectXDevice>(DirectXDevice* pDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			pDirectXDevice = nullptr;
			#else
			pDirectXDevice = new DirectX9Device();
			#endif
		}

		static void Create(DirectXGraphicDevice* pDirectXGraphicDevice, DirectXDevice* pDirectXDevice)
		{
			#ifdef DIRECT_X_VERSION_11
			pDirectXGraphicDevice = nullptr;
			#else
			pDirectXGraphicDevice = new DirectX9GraphicDevice(pDirectXDevice);
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
