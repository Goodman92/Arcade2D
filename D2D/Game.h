#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "GameTimer.h"
#include "Testlevel.h"

class Game {

public:
	Game(HINSTANCE instance);
	HRESULT Initialize();
	void RunMessageLoop();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	//proto
	Baselevel* factory(int choice);

private:
	//Baselevel baselevel;
	HINSTANCE m_instance;
	//HWND m_hwnd;
	Baselevel* m_level;
	GameTimer m_timer;
	Keyboard m_keyboard;
	GoodmanEngine::Graphics* m_pGraphics;

};

Game::Game(HINSTANCE instance) {
	m_pGraphics = GoodmanEngine::Graphics::getInstance();
	m_instance = instance;
//	dynamic_cast<Testlevel*>(m_level);
}

Baselevel* Game::factory(int choice) {
	switch (choice) {
	case 1:
		return new Testlevel;
	}
}

HRESULT Game::Initialize()
{
	HRESULT hr;

	hr = m_pGraphics->CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Game::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = m_instance;
		wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"GoodmanEngine";

		RegisterClassEx(&wcex);

		FLOAT dpiX, dpiY;

		m_pGraphics->getFactory()->GetDesktopDpi(&dpiX, &dpiY);

		m_pGraphics->m_hwnd = CreateWindow(
			L"GoodmanEngine",
			L"paskaap",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
			static_cast<UINT>(ceil(490.f * dpiY / 96.f)),
			NULL,
			NULL,
			m_instance,
			this
		);
		hr = m_pGraphics->m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_pGraphics->m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_pGraphics->m_hwnd);
		}
	}

	return hr;
}

void Game::RunMessageLoop()
{
	MSG msg;

	//proto
	m_level = factory(1);
	m_pGraphics->CreateDeviceResources(m_pGraphics->m_hwnd);

	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	while (msg.message != WM_QUIT) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (m_timer.delta() >= m_timer.getClockRate()) {
			m_level->run();
			m_timer.resetClock();
		}
		m_timer.clockTick();
	}

}

LRESULT CALLBACK Game::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		Game *engine = (Game *)pcs->lpCreateParams;
		::SetWindowLongPtrW(hwnd,GWLP_USERDATA,PtrToUlong(engine));
		result = 1;
	}
	else
	{
		Game *engine = reinterpret_cast<Game *>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hwnd,GWLP_USERDATA)));
		bool wasHandled = false;
		if (engine)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				engine->m_pGraphics->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;
			/*
			case WM_CHAR:
				OutputDebugString(L"WM_CHAR");
			break;
			*/
			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_PAINT:
			{
				//	engine->OnRender();
				ValidateRect(hwnd, NULL);
			}
			result = 0;
			wasHandled = true;
			break;

			case WM_KEYDOWN:
			{
				auto key = engine->m_keyboard.handleInput(wParam);
				if (key == KEYSTROKES::duck) {
					OutputDebugString(L"duck! \n");

				}
				if (key == KEYSTROKES::right) {
					OutputDebugString(L"right! \n");

				}
				if (key == KEYSTROKES::jump) {
					OutputDebugString(L"jump! \n");

				}
				if (key == KEYSTROKES::left) {
					OutputDebugString(L"left! \n");
				}
				if (key == KEYSTROKES::multikeys) {
					OutputDebugString(L"multikeys! \n");
				}
				if (key == KEYSTROKES::multikeys) {
					engine->m_level->handleMultiKeyStrokes(engine->m_keyboard.getPressedKeys());
				}
				else {
					engine->m_level->handleKeyStroke(key);
				}
			}
			break;
			
			case WM_KEYUP: 
			{
				engine->m_keyboard.pop(wParam);
				engine->m_level->handleRelease(wParam);
			}
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}
