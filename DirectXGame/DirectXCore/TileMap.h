#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "Camera.h"

class TileMap
{
public:
	TileMap();
	TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t *path);
	void SetCamera(Camera* _cam) { mainCamera = _cam; }
	void Render();
	~TileMap();
private:
	DirectX::SimpleMath::Vector2 m_screenPos;
	std::vector<Sprite> tileCells;
	Tmx::Map *tilemap;
	std::map<int, Sprite*> listTileset;
	Camera* mainCamera;
	DirectXCore::DeviceResources* deviceResource;
};

