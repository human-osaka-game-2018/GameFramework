#include "DirectX8Mouse.h"

namespace gameframework
{
	void DirectX8Mouse::Create()
	{
		LPDIRECTINPUT directXInputDevice = nullptr;
		DirectXParam::GetDirectXInputDevice()->Get(&directXInputDevice);

		directXInputDevice->CreateDevice(
			GUID_SysMouse,
			&m_pInputDevice,
			NULL);

		m_pInputDevice->SetDataFormat(&c_dfDIMouse);

		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		m_pInputDevice->SetCooperativeLevel(
			hWnd,
			DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

		DIPROPDWORD mouseProp;
		mouseProp.diph.dwSize = sizeof(DIPROPDWORD);
		mouseProp.diph.dwHeaderSize = sizeof(mouseProp.diph);
		mouseProp.diph.dwObj = 0;
		mouseProp.diph.dwHow = DIPH_DEVICE;
		mouseProp.dwData = DIPROPAXISMODE_REL;

		m_pInputDevice->SetProperty(DIPROP_AXISMODE, &mouseProp.diph);
	}

	void DirectX8Mouse::AcquireInputState()
	{
		//マウスの状態を取得する権限の取得
		m_pInputDevice->Acquire();

		//ここではまだディスプレイ基準の絶対座標
		GetCursorPos(&m_cursorRelativePos);

		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		//ここでウィンドウ基準の相対座標に変換
		ScreenToClient(hWnd, &m_cursorRelativePos);

		//マウスの状態を取得
		m_pInputDevice->GetDeviceState(
			sizeof(DIMOUSESTATE),
			&m_state);
	}

	void DirectX8Mouse::CheckInputStateDetatils()
	{
		bool isInputtedPrev = false;
		bool isInputted = false;

		ZeroMemory(&m_details, sizeof(bool) * DIM_MAX);

		for (int i = 0; i < DIM_MAX; ++i)
		{
			isInputtedPrev = IsInputted(m_prevState.rgbButtons[i]);
			isInputted     = IsInputted(m_state.rgbButtons[i]);

			if (isInputtedPrev)
			{
				m_details[i] = (isInputted) ? IND_HOLD : IND_RELEASE;

				continue;
			}

			m_details[i] = (isInputted) ? IND_PRESS : IND_NEUTRAL;
		}
	}
}
