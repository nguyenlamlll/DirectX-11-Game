#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "GameObject.h"
#include "Collider.h"
#include "Renderer.h"
#include "QuadTree.h"

namespace DirectXCore
{
	class TileMap
	{
	public:
		TileMap();
		TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t * _imagePath, const wchar_t * _txtPath, int _columns, int _rows, int _mapTileColumnCount, int _mapTileRowCount);
		TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t *path);
		void SetCamera(Camera* _cam) { mainCamera = _cam; }
		void Update();
		void Render();
		SimpleMath::Vector3 GetTilemapPosition() { return position; }
		SimpleMath::Vector3 GetTilemapScale() { return scale; }
		void SetTilemapPosition(SimpleMath::Vector3 _tilemapPosition);
		void SetTilemapScale(SimpleMath::Vector3 _scale);
		QuadTree* GetQuadTree() { return thisQuad; }
		std::vector<GameObject*>* GetListGameObjects() { return gameObjectList; }
		std::vector<GameObject*>* GetListAreas() { return listAreas; }
		RECT* GetRegion() { return newRegion; }
		Vector3 GetMapSize() { return mapSize; }
		~TileMap();

		std::map<int, RECT*> GetListTileIDs() { return listTileID; };
		std::vector<int>* GetData() { return data; };
		std::map<int, Vector3>* GetPositionList() { return positionList; };
		Renderer* GetTilepRenderer() { return thisRenderer; }
	private:
		DirectX::SimpleMath::Vector3 position, worldToScreenPosition, scale;
		Tmx::Map *tilemap;
		std::map<int, Sprite*> tilesetSheet;
		std::map<int, RECT*> listTileID;
		std::map<int, Vector3> listRECTPositions;
		std::vector<GameObject*> listRenderers;
		Camera* mainCamera;
		DirectXCore::DeviceResources* deviceResource;
		std::vector<GameObject*>* gameObjectList;
		std::vector<GameObject*>* listAreas;
		Renderer* thisRenderer;
		QuadTree* thisQuad;
		RECT* newRegion;
		std::vector<int>* data;
		std::map<int, Vector3>* positionList;
		Vector3 mapSize;
	};
}


