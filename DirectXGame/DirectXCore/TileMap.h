#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "Collider.h"
#include "Renderer.h"

namespace DirectXCore
{
	class TileMap
	{
	public:
		TileMap();
		TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t *path);
		void SetCamera(Camera* _cam) { mainCamera = _cam; }
		void Update();
		void Render();
		std::vector<GameObject*>* GetListGameObjects() { return gameObjectList; }
		~TileMap();
	private:
		DirectX::SimpleMath::Vector3 position,worldToScreenPosition;
		Tmx::Map *tilemap;
		std::map<int, Sprite*> tilesetSheet;
		std::map<int, RECT*> listTileID;
		std::map<int, Vector3> listRECTPositions;
		Camera* mainCamera;
		DirectXCore::DeviceResources* deviceResource;
		std::vector<GameObject*>* gameObjectList;
	};
}


