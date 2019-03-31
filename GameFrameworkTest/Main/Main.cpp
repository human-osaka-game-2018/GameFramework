#include <Windows.h>
#include <tchar.h>

#include <GameFramework.h>

#include "../GraphicEffects/ClickEffect.h"
#include "../GraphicEffects/Cursor.h"
#include "../GraphicEffects/HoldEffect.h"

using namespace gameframework;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	WindowParam::SetInstanceHandle(hInst);

	//デフォルトでは1280.0f 720.0f
	WindowParam::SetWindowSize(RectSize(1600.0f, 900.0f));

	Window* pWindow = new Window(_T("Summoners'Aster"));

	//インスタンスが一つしかないものを自動開放するように登録
	SingletonHolder<Window>::Create(pWindow);

	//DirectXのデバイスを作成
	DirectXParam::Create();

	GameFramework& rGameFramework = GameFramework::CreateAndGetRef();

	int frameCount = 0;

	Cursor cursor;

	while (!pWindow->ReceivedQuitMessage())
	{
		if (pWindow->ReceivedWinMessage()) continue;

		if (!rGameFramework.CanStartNextFrame()) continue;

		rGameFramework.PrepareInFrame();

		if (rGameFramework.MouseIsPressed(DirectX8Mouse::DIM_LEFT))
		{
			rGameFramework.RegisterGraphicEffect(new ClickEffect());
		}

		if (rGameFramework.MouseIsHeld(DirectX8Mouse::DIM_LEFT) && !((frameCount++) % 3))
		{
			rGameFramework.RegisterGraphicEffect(new HoldEffect());
		}

		rGameFramework.UpdateGraphicEffects();
		rGameFramework.RenderGraphicEffects();

		cursor.Update();
		cursor.Render();

		rGameFramework.FinishInFrame();
	}

	return 0;
}
