//----------------------------------------------------------
// <filename>DirectXDevice.h</filename>
//----------------------------------------------------------

#ifndef DIRECT_X_DEVICE_H
#define DIRECT_X_DEVICE_H

#include <Windows.h>

#include <d3dx9.h>

/// <summary>
/// 基礎構築をに関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	using LPDIRECT3D = ID3D11Device*;
	#else
	using LPDIRECT3D = LPDIRECT3D9;
	#endif //! DIRECT_X_VERSION_11
		
	/// <summary>
	/// DirectXのデバイスクラス
	/// </summary>
	class DirectXDevice
	{
	public:
		virtual ~DirectXDevice()
		{
			m_pDirectXDevice->Release();
			delete m_pDirectXDevice;
		}

		inline void Get(LPDIRECT3D* ppDirectXDevice) const
		{
			*ppDirectXDevice = m_pDirectXDevice;
		}

	protected:
		DirectXDevice() {};

		/// <summary>
		/// DirectXのデバイスを作成する
		/// </summary>
		virtual void Create() = 0;

		LPDIRECT3D m_pDirectXDevice = nullptr;

	private:
		DirectXDevice(const DirectXDevice& rhs) = delete;

		DirectXDevice& operator=(const DirectXDevice& rhs) = delete;
	};
}

#endif //! DIRECT_X_DEVICE_H
