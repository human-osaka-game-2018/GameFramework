//----------------------------------------------------------
// <filename>DirectX9GraphicDevice.cpp</filename>
//----------------------------------------------------------

#include "DirectX9GraphicDevice.h"

namespace gameframework
{
	void DirectX9GraphicDevice::DirectXPresentParam::FormatUnionParam(D3DPRESENT_PARAMETERS* pD3DPRESENT_PARAMETERS)
	{
		ZeroMemory(pD3DPRESENT_PARAMETERS, sizeof(D3DPRESENT_PARAMETERS));

		RectSize windowSize;
		WindowParam::GetWindowSize(&windowSize);
		pD3DPRESENT_PARAMETERS->BackBufferWidth = static_cast<UINT>(windowSize.m_width);
		pD3DPRESENT_PARAMETERS->BackBufferHeight = static_cast<UINT>(windowSize.m_height);

		pD3DPRESENT_PARAMETERS->BackBufferFormat = D3DFMT_X8R8G8B8;
		pD3DPRESENT_PARAMETERS->BackBufferCount = 1;

		pD3DPRESENT_PARAMETERS->SwapEffect = D3DSWAPEFFECT_DISCARD;

		pD3DPRESENT_PARAMETERS->EnableAutoDepthStencil = true;
	}

	void DirectX9GraphicDevice::Create(DirectXDevice* pDirectXDevice)
	{
		HWND hWnd = nullptr;
		WindowParam::GetWindowHandle(&hWnd);

		LPDIRECT3D pDirect3D = nullptr;
		pDirectXDevice->Get(&pDirect3D);

		D3DPRESENT_PARAMETERS directXPresentParams;
		DirectXPresentParam::GetWindowModeParam(&directXPresentParams);

		if (SUCCEEDED(pDirect3D->CreateDevice(

			//描画をハードウェアに依存させる 軽い
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
			&directXPresentParams,
			&m_pDirectXGraphicDevice)))
		{
			return;
		}

		MessageBox(
			0,
			_T("REFモードで再試行します"),
			_T("HALモードでDirectXのグラフィックデバイスを作成できませんでした"),
			MB_OK);

		if (SUCCEEDED(pDirect3D->CreateDevice(
			//描画をソフトウェアに依存させる 重い
			D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
			&directXPresentParams,
			&m_pDirectXGraphicDevice)))
		{
			return;
		}

		MessageBox(
			0,
			_T("アプリケーションを終了します"),
			_T("DirectXのグラフィックデバイスを作成できませんでした"),
			MB_OK | MB_ICONERROR);

		PostQuitMessage(0);
	}
}
