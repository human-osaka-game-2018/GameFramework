//----------------------------------------------------------
// <filename>DirectXInput8Device.cpp</filename>
//----------------------------------------------------------

#include "DirectX8InputDevice.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX8InputDevice::Create()
	{
		HINSTANCE hInstance = nullptr;
		WindowParam::GetInstanceHandle(&hInstance);

		if (SUCCEEDED(DirectInput8Create(
			hInstance,
			DIRECTINPUT_VERSION, IID_IDirectInput8,
			(void**)&m_pDirectXInputDevice,
			NULL)))
		{
			return;
		}

		MessageBox(
			0,
			_T("アプリケーションを終了します"),
			_T("DirectXの入力デバイスを作成できませんでした"),
			MB_OK | MB_ICONERROR);

		PostQuitMessage(0);
	}

	#endif //DIRECT_X_VERSOIN_9
}
