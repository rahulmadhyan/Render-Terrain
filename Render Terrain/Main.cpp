//#include <Windows.h>
#include "Window.h"
#include "Graphics.h"

using namespace std;
using namespace graphics;
using namespace window;

static const LPCWSTR	appName = L"Directx 12 Terrain Renderer";
static const int		WINDOW_HEIGHT = 1080;	// dimensions for the window we're making.
static const int		WINDOW_WIDTH = 1920;
static const bool		FULL_SCREEN = false;

static void KeyUp(UINT key) {
	switch (key) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return;
	}
}
static LRESULT CALLBACK WndProc(HWND win , UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_DESTROY:
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_KEYUP:
			KeyUp((UINT)wp);
			break;
		default:
			return DefWindowProc(win, msg, wp, lp);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int cmdShow) {
	try {
		Window WIN(appName, WINDOW_HEIGHT, WINDOW_WIDTH, WndProc, FULL_SCREEN);
		Graphics GFX(WINDOW_HEIGHT, WINDOW_WIDTH, WIN.GetWindow(), FULL_SCREEN);
	
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		while (1) {
			if (PeekMessage(&msg, WIN.GetWindow(), 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} 
			if (msg.message == WM_QUIT) { 
				return 1;
			}

			GFX.Render();
		}

		return 2;
	} catch (GFX_Exception& e) {
		OutputDebugStringA(e.what());
		return 3;
	} catch (Window_Exception& e) {
		OutputDebugStringA(e.what());
		return 4;
	}
}