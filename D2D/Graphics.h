#pragma once

#ifndef WINVER              // windows =<7
#define WINVER 0x0700       // koska UWP ja ympäristönä w7
#endif

#ifndef _WIN32_WINNT        // windows =<7
#define _WIN32_WINNT 0x0700 // koska UWP ja ympäristönä w7
#endif

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN     // MSDN poistetaan turhat

#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <stdio.h>


#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwrite.h>
#include "Release.h"
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")
#pragma comment(lib, "windowscodecs")

struct Dimensions {
	Dimensions() {
		m_x = m_xw = m_y = m_yh = 0.0f;
	}
	float m_x;  //piirtoaloitus x-koord
	float m_y;	//piirtoaloitus y-koord
	float m_xw;	//kuvan leveys
	float m_yh; //kuvan korkeus
};

struct ComponentPlacement {
	ComponentPlacement() {
		m_x = m_xw = m_y = m_yh = x = y = 0.0f;
	}
	float x;  //sijainti x-koord
	float y;  //sijainti y-koord
	float m_x;  //piirtoaloitus x-koord
	float m_y;	//piirtoaloitus y-koord
	float m_xw;	//kuvan leveys
	float m_yh; //kuvan korkeus
};

namespace GoodmanEngine {
	class Graphics {

	public:
		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources(HWND m_hwnd);
		void DiscardDeviceResources();
		void OnResize(UINT width,UINT height);

		inline HWND getWindowHandle();
		inline ID2D1Factory* getFactory();
		inline ID2D1HwndRenderTarget* getRenderTarget();
		static Graphics* getInstance();
		HWND m_hwnd;

		bool getWindowsDimensions(RECT& rc) {
			return GetClientRect(m_hwnd, &rc);
		}

	private:
		static Graphics* instance;
		Graphics();
		~Graphics();
		ID2D1Factory *m_pD2DFactory;
		ID2D1HwndRenderTarget *m_pRenderTarget;

	};

	Graphics::Graphics() : m_hwnd(NULL), m_pD2DFactory(NULL), m_pRenderTarget(NULL) { }

	Graphics::~Graphics()
	{
		SafeRelease(&m_pD2DFactory);
		SafeRelease(&m_pRenderTarget);
	}

	Graphics* Graphics::getInstance() {
		if (!instance) {
			instance = new Graphics();
		}
		return instance;
	}

	HWND Graphics::getWindowHandle() {
		return m_hwnd;
	}

	ID2D1Factory* Graphics::getFactory() {
		return m_pD2DFactory;
	}

	ID2D1HwndRenderTarget* Graphics::getRenderTarget() {
		return m_pRenderTarget;
	}

	// luo d3d device, resurssit pitää luoda uudelleen jos device katoaa
	HRESULT Graphics::CreateDeviceResources(HWND m_hwnd)
	{
		HRESULT hr = S_OK;

		if (!m_pRenderTarget)
		{
			RECT rc;
			GetClientRect(m_hwnd, &rc);
			D2D1_SIZE_U size = D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top
			);

			// d2d spesifinen render targetti eli mihin renderataan
			hr = m_pD2DFactory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(m_hwnd, size),
				&m_pRenderTarget
			);
		}

		return hr;
	}

	void Graphics::DiscardDeviceResources()
	{
		SafeRelease(&m_pRenderTarget);
	}

	HRESULT Graphics::CreateDeviceIndependentResources()
	{
		HRESULT hr = S_OK;
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		return hr;
	}

	void Graphics::OnResize(UINT width, UINT height)
	{
		if (m_pRenderTarget)
		{
			m_pRenderTarget->Resize(D2D1::SizeU(width, height));
		}
	}
	Graphics *Graphics::instance = NULL;
}