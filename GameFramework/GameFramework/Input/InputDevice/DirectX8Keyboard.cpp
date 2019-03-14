#include "DirectX8Keyboard.h"

namespace gameframework
{
	void DirectX8Keyboard::Create()
	{
		LPDIRECTINPUT directXInputDevice = nullptr;
		DirectXParam::GetDirectXInputDevice()->Get(&directXInputDevice);

		directXInputDevice->CreateDevice(
			GUID_SysKeyboard, &m_pInputDevice,
			NULL);

		m_pInputDevice->SetDataFormat(&c_dfDIKeyboard);

		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		m_pInputDevice->SetCooperativeLevel(
			hWnd,
			DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void DirectX8Keyboard::CheckInputStateDetatils()
	{
		bool isInputtedPrev = false;
		bool isInputted = false;

		ZeroMemory(m_details, sizeof(bool) * KEY_MAX);

		for (int i = 0; i < KEY_MAX; ++i)
		{
			isInputtedPrev = IsInputted(m_prevDiks[i]);
			isInputted	   = IsInputted(m_diks[i]);

			if (isInputtedPrev)
			{
				m_details[i] = (isInputted) ? IND_HOLD : IND_RELEASE;

				continue;
			}

			m_details[i] = (isInputted) ? IND_PRESS : IND_NEUTRAL;
		}
	}
}
