#include "DirectX9Renderer.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9Renderer::PrepareInFrame()
	{
		m_pDirectXGraphicDevice->Clear(
			0,
			NULL,

			//ZBUFFERもクリア
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,

			//画面をクリアするときの色
			D3DCOLOR_XRGB(0, 0, 0),
			1.f,
			0);

		m_pDirectXGraphicDevice->BeginScene();
	}

	void DirectX9Renderer::FinishInFrame()
	{
		m_pDirectXGraphicDevice->EndScene();
		m_pDirectXGraphicDevice->Present(
			NULL,
			NULL,
			NULL,
			NULL);
	}

	#endif //DIRECT_X_VERSOIN_9
}
