#pragma once
#include "ResourceLoader.h"
#include "GameComponent.h"
#include <map>
#include "Map.h"
//KOMPOSIITTI VAI PERINTÄ?

// BITMAP RELEASE?!?!?!?!?!?!
class Scene : public GoodmanEngine::ResourceLoader {
public:
	Scene();
	void startDrawing();
	void endDrawing();
	void update();
	void setGameComponents(GameComponent* gameComponent);
	void setMapComponent(Map* map);
	bool fionalisti(RECT& r);
	void gravity();
private:
	void initializeBitmapForGameComponent(GameComponent* gameComponent);
	std::map<ID2D1Bitmap*, GameComponent*> m_ppCorrespondingBitmaps;
	std::pair<Map*, ID2D1Bitmap*> m_ppMapComponent;
};

Scene::Scene() : GoodmanEngine::ResourceLoader() { }

void Scene::setGameComponents(GameComponent* gameComponent) {
	initializeBitmapForGameComponent(gameComponent);
}

void Scene::setMapComponent(Map* map) {
	auto bmpTiles = loadImageFromFile(map->getTileImage());
	m_ppMapComponent = std::make_pair(map, bmpTiles);
}

void Scene::initializeBitmapForGameComponent(GameComponent* gameComponent) {
	auto bmp = loadImageFromFile(gameComponent->getImage());
	m_ppCorrespondingBitmaps.insert(std::make_pair(bmp, gameComponent));
}

bool Scene::fionalisti(RECT& r) {
	return getGraphics()->getWindowsDimensions(r);
}

void Scene::startDrawing() {
	getGraphics()->getRenderTarget()->BeginDraw();
	getGraphics()->getRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Scene::endDrawing() {
	getGraphics()->getRenderTarget()->EndDraw();
}

void Scene::gravity() {
	//game objektilla metodi, type -> palauttaa objektin tyypin esim: movable, solid, jne
	// tarkastetaa tyyppi, applytään voima jos ei olla groundilla, voiman pitäisi kasvaa koko ajan

}

void Scene::update() {
	startDrawing();
	ComponentPlacement dim;
	gravity();
	for (auto& component : m_ppCorrespondingBitmaps) {
		dim = component.second->getDimensions();
		getGraphics()->getRenderTarget()->DrawBitmap(component.first,
			D2D1::RectF(
				dim.x, dim.y, dim.x + dim.m_xw, dim.y + dim.m_yh
			), 0.5f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(dim.m_x, dim.m_y, dim.m_x + dim.m_xw, dim.m_y + dim.m_yh));
		component.second->animate();
	}
	
	auto map = m_ppMapComponent.first;
	auto tiles = map->getTilePositions();

	for (auto e : tiles) {
		getGraphics()->getRenderTarget()->DrawBitmap(m_ppMapComponent.second,
			D2D1::RectF(
				e.at(0), e.at(1), e.at(0) + e.at(2), e.at(1) + 70
			), 0.5f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(576, 864, 576 + e.at(2), 864 + 70));
	}

	endDrawing();
}
