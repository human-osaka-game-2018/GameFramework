//----------------------------------------------------------
// <filename>DirectX9Device.cpp</filename>
//----------------------------------------------------------

#include "DirectX9Device.h"

#include <Windows.h>
#include <tchar.h>

#include <d3dx9.h>

#include "DirectXDevice.h"

namespace gameframework
{
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
}
