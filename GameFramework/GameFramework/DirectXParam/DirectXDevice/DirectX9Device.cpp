//----------------------------------------------------------
// <filename>DirectX9Device.cpp</filename>
//----------------------------------------------------------

#include "DirectX9Device.h"

namespace gameframework
{
	#ifndef DIRECT_X_VERSOIN_11

	void DirectX9Device::Create()
	{
		if (m_pDirectXDevice = Direct3DCreate9(D3D_SDK_VERSION))
		{
			return;
		}

		MessageBox(
			0,
			_T("アプリケーションを終了します"),
			_T("DirectXDeviceの作成に失敗しました"),
			MB_OK | MB_ICONERROR);

		PostQuitMessage(0);
	}

	#endif //! DIRECT_X_VERSOIN_11
}
