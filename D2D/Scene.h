#pragma once
#include "ResourceLoader.h"
//KOMPOSIITTI VAI PERINTÄ?
class Scene : public GoodmanEngine::ResourceLoader {
public:
	Scene();
	void drawImage(PCWSTR uri, UINT posx, UINT posy, UINT x, UINT y, UINT xw, UINT yh);
	void drawBackground(PCWSTR uri, UINT dw, UINT dh);
	void startDrawing();
	void endDrawing();
	void update();
private:
	GoodmanEngine::ResourceLoader m_resourceLoader;
};

Scene::Scene() : GoodmanEngine::ResourceLoader() { }

void Scene::drawImage(PCWSTR uri, UINT posx, UINT posy, UINT x, UINT y, UINT xw, UINT yh) {

	auto bmp = loadImageFromFile(uri);
	getGraphics()->getRenderTarget()->DrawBitmap(bmp,
		D2D1::RectF(
			posx, posy, xw, yh
		), 0.5f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(x, y, x+xw, y+yh));
}

void Scene::drawBackground(PCWSTR uri, UINT dw, UINT dh) {

	auto bmp = loadImageFromFile(uri);
	getGraphics()->getRenderTarget()->DrawBitmap(bmp,
		D2D1::RectF(
			0, 0, 640,480
		), 0.5f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(dw, dh, bmp->GetSize().width / 2 + dw, bmp->GetSize().height + dh));
}

void Scene::startDrawing() {
	getGraphics()->getRenderTarget()->BeginDraw();
	getGraphics()->getRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Scene::endDrawing() {
	getGraphics()->getRenderTarget()->EndDraw();
}

void Scene::update() { }