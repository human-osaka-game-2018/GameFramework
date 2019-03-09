//----------------------------------------------------------
// <filename>DirectXInputDevice.h</filename>
//----------------------------------------------------------

#ifndef DIRECT_X_INPUT_DEVICE_H
#define DIRECT_X_INPUT_DEVICE_H

#include <Windows.h>

#include <dinput.h>

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	//using LPDIRECTINPUT = LPDIRECTINPUT8;
	#else
	using LPDIRECTINPUT = LPDIRECTINPUT8;
	#endif //! DIRECT_X_VERSION_11
		
	/// <summary>
	/// DirectXのインプットデバイスクラス
	/// </summary>
	class DirectXInputDevice
	{
	public:
		DirectXInputDevice() {};

		virtual ~DirectXInputDevice()
		{
			m_pDirectXInputDevice->Release();
			delete m_pDirectXInputDevice;
		}

		inline void Get(LPDIRECTINPUT* ppDirectXInputDevice) const
		{
			*ppDirectXInputDevice = m_pDirectXInputDevice;
		}

	protected:
		/// <summary>
		/// DirectXのインプットデバイスを作成する
		/// </summary>
		virtual void Create() = 0;

		LPDIRECTINPUT m_pDirectXInputDevice = nullptr;

	private:
		DirectXInputDevice(const DirectXInputDevice& rhs) = delete;

		DirectXInputDevice& operator=(const DirectXInputDevice& rhs) = delete;
	};
}

#endif //! DIRECT_X_INPUT_DEVICE_H
