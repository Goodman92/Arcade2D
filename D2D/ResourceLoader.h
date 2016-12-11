#pragma once

namespace GoodmanEngine 
{
	class ResourceLoader {
	public:
		ResourceLoader();
		ID2D1Bitmap* loadImageFromFile(PCWSTR uri);
		inline HWND getWindowsHandle();
		inline Graphics* getGraphics();
		void drawText(const WCHAR* str);
	private:
		Graphics* m_pGraphics;
		ID2D1Bitmap* m_pBmp;
		const WCHAR* buf;

	};

	HWND ResourceLoader::getWindowsHandle() {
		return m_pGraphics->getWindowHandle();
	}
	ResourceLoader::ResourceLoader() {
		m_pGraphics = GoodmanEngine::Graphics::getInstance();
		m_pBmp = NULL;
	}
	
	Graphics* ResourceLoader::getGraphics() {
		return m_pGraphics;
	}
	
	ID2D1Bitmap* ResourceLoader::loadImageFromFile(PCWSTR uri) {
		//jee :D
		m_pGraphics->CreateDeviceResources(m_pGraphics->m_hwnd);
		HRESULT hr = S_OK;
		IWICBitmapDecoder *pDecoder = NULL;
		IWICBitmapFrameDecode *pSource = NULL;
		IWICStream *pStream = NULL;
		IWICFormatConverter *pConverter = NULL;
		IWICBitmapScaler *pScaler = NULL;

		IWICImagingFactory *wicFactory = NULL;

		CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&wicFactory);

		hr = wicFactory->CreateDecoderFromFilename(
			uri,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);


		if (SUCCEEDED(hr)) {
			hr = pDecoder->GetFrame(0, &pSource);
		}

		if (SUCCEEDED(hr)) {
			// muutetaan kuva, transparenttia?
			hr = wicFactory->CreateFormatConverter(&pConverter);
		}


		if (SUCCEEDED(hr)) {
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}

		if (SUCCEEDED(hr))
		{
			//bitmapin alustus
			hr = m_pGraphics->getRenderTarget()->CreateBitmapFromWicBitmap(
				pConverter,
				NULL,
				&m_pBmp
			);
		}
		if (pDecoder) {
			pDecoder->Release();
		}
		if (pSource) {
			pSource->Release();

		}
		if (pConverter) {
			pConverter->Release();
		}
		if (pStream)
			pStream->Release();
		if (pScaler)
			pScaler->Release();
		if (wicFactory)
			wicFactory->Release();
		return m_pBmp;
	}

	void ResourceLoader::drawText(const WCHAR* str) {
		buf = str;
		static const WCHAR msc_fontName[] = L"Verdana";
		static const FLOAT msc_fontSize = 50;
		IDWriteFactory* m_pDWriteFactory = NULL;
		IDWriteTextFormat* m_pTextFormat = NULL;

		HRESULT hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown **>(&m_pDWriteFactory)
			);

		if (SUCCEEDED(hr)) {
			hr = m_pDWriteFactory->CreateTextFormat(
				msc_fontName,
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				msc_fontSize,	
				L"", //locale
				&m_pTextFormat
			);
		}
		if (SUCCEEDED(hr)) {
			m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}

		D2D1_SIZE_F renderTargetSize = m_pGraphics->getRenderTarget()->GetSize();
		m_pGraphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		//m_graphics.getRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));

		ID2D1Brush* brush = NULL;
		ID2D1SolidColorBrush* jee = NULL;
		m_pGraphics->getRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &jee);
		std::wcslen(buf);
		m_pGraphics->getRenderTarget()->DrawTextW(
			buf,
			std::wcslen(buf),
			m_pTextFormat,
			D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
			jee
			);
		}
}