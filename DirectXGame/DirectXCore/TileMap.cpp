#include "stdafx.h"
#include "TileMap.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace DirectXCore;

TileMap::TileMap()
{
}

DirectXCore::TileMap::TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t * _imagePath, const wchar_t * _txtPath, int _columns, int _rows, int _mapTileColumnCount, int _mapTileRowCount)
{
	mapSize = Vector3(0, 0, 0);
	position = Vector3(0, 0, 0);
	scale = Vector3(3, 3, 1);
	worldToScreenPosition = position;
	gameObjectList = new std::vector<GameObject*>();
	std::ifstream file("Resources/00/Charleston_1_1.CSV");
	data = new std::vector<int>();
	positionList = new std::map<int, Vector3>();
	if (file.good())
	{
		std::string curData = "";

		int i = 0;
		while (file >> curData)
		{
			i++;
			int x = atoi(curData.c_str());
			if (x != 0)
				data->push_back(x);
		}
		file.close();
	}
	//INIT
	for (size_t m = 0; m < _rows; m++)
	{
		for (size_t n = 0; n < _columns; n++)
		{
			RECT* sourceRECT = new RECT();
			int tileSetHorizontalCount = 20;
			int tileSetVerticalCount = 4;

			//tile index
			int tileID = (m * 20) + n;
			int dataYIndex = tileID / tileSetHorizontalCount;
			int dataXIndex = tileID % tileSetHorizontalCount;

			sourceRECT->top = dataYIndex * 16;
			sourceRECT->bottom = sourceRECT->top + 16;
			sourceRECT->left = dataXIndex * 16;
			sourceRECT->right = sourceRECT->left + 16;

			listTileID.insert(std::pair<int, RECT*>(tileID, sourceRECT));


			//listRECTPositions.insert(std::pair<int,Vector3>(tileID, Vector3((n * tileDataWidth) + position.x, (m * tileDataHeight) + position.y, 0)));
		}
	}
	for (size_t m = 0; m < _mapTileRowCount; m++)
	{
		for (size_t n = 0; n < _mapTileColumnCount; n++)
		{
			DirectX::SimpleMath::Vector3* currentPosition = new Vector3(((n * 16) + 16 / 2), ((m * 16) + 16 / 2), 0);
			*currentPosition *= scale;
			int tileIndex = (m * _mapTileColumnCount) + n;
			positionList->insert(std::pair<int, Vector3>(tileIndex, *currentPosition));
			if (data->at(tileIndex) == 57 || data->at(tileIndex) == 57 || data->at(tileIndex) == 12 || data->at(tileIndex) == 13 || data->at(tileIndex) == 14 || data->at(tileIndex) == 37 || data->at(tileIndex) == 61 || data->at(tileIndex) == 62)
			{
				GameObject*gameObject = new GameObject();
				gameObject->GetTransform()->SetPosition(position + *currentPosition);
				gameObject->GetTransform()->SetScale(Vector3(16 * scale.x, 16 * scale.y, 1));
				gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
				gameObject->SetTag("Wall");
				gameObjectList->push_back(gameObject);
			}
		}
	}
	thisRenderer = new Renderer(_deviceResource, _imagePath);
	thisRenderer->SetPivot(Vector3(16 / 2, 16 / 2, 0));
	mapSize.x = _mapTileColumnCount*scale.x*16;
	mapSize.y = _mapTileRowCount*scale.y*16;
}

TileMap::TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t * path)
{
	gameObjectList = new std::vector<GameObject*>();
	listAreas = new std::vector<GameObject*>();
	deviceResource = _deviceResource;
	tilemap = new Tmx::Map;
	std::wstring ws(path);
	std::string pathstr(ws.begin(), ws.end());
	tilemap->ParseFile(pathstr);
	position = Vector3(0, 0, 0);
	scale = Vector3(3, 3, 1);
	worldToScreenPosition = position;

	newRegion = new RECT();
	newRegion->left = newRegion->top = 0;
	newRegion->right = tilemap->GetWidth()*tilemap->GetTileWidth()*scale.x;
	newRegion->bottom = tilemap->GetHeight()*tilemap->GetTileHeight()*scale.y;

	thisQuad = new QuadTree(newRegion, 1, 5);

	for (size_t i = 0; i < tilemap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = tilemap->GetTileset(i);
		int as = tileset->GetTileWidth();
		//std::string username = "Resources/" + tileset->GetImage()->GetSource();// old tilemap
		std::string username = "Resources/Captain/Maps/" + tileset->GetImage()->GetSource();// old tilemap
		//std::string username = "Resources/" + tileset->GetImageInTileset()->GetSource();// new tilemap
		std::wstring wideusername;
		for (int i = 0; i < username.length(); ++i) wideusername += wchar_t(username[i]);
		const wchar_t* spritePath = wideusername.c_str();

		thisRenderer = new Renderer(_deviceResource, spritePath);
		thisRenderer->SetPivot(Vector3(tileset->GetTileWidth() / 2, tileset->GetTileHeight() / 2, 0));
		//thisRenderer->SetPivot(Vector3(0, 0, 0));
	}
	for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = tilemap->GetTileLayer(i);
		if (!layer->IsVisible()) continue;
		int tileDataWidth = tilemap->GetTileWidth();
		int tileDataHeight = tilemap->GetTileHeight();
		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				RECT* sourceRECT = new RECT();
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);
				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = tilemap->GetTileset(tilesetIndex);
					int tileSetHorizontalCount = tileSet->GetImage()->GetWidth() / tileDataWidth;
					int tileSetVerticalCount = tileSet->GetImage()->GetHeight() / tileDataHeight;

					//tile index
					int tileID = layer->GetTileId(n, m);
					int dataYIndex = tileID / tileSetHorizontalCount;
					int dataXIndex = tileID % tileSetHorizontalCount;

					sourceRECT->top = dataYIndex * tileDataHeight;
					sourceRECT->bottom = sourceRECT->top + tileDataHeight;
					sourceRECT->left = dataXIndex * tileDataWidth;
					sourceRECT->right = sourceRECT->left + tileDataWidth;

					listTileID.insert(std::pair<int, RECT*>(tileID, sourceRECT));
					//listRECTPositions.insert(std::pair<int,Vector3>(tileID, Vector3((n * tileDataWidth) + position.x, (m * tileDataHeight) + position.y, 0)));
				}
			}
		}
	}
	for (size_t i = 0; i < tilemap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = tilemap->GetObjectGroup(i);
		if (objectGroup->GetName() == "BackLayer") {
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++) {
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				listRenderers.at(j)->GetTransform()->SetPosition(Vector3(object->GetX(), object->GetY(), 0));
			}
		}
		else if (objectGroup->GetName() == "Area")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *gameObject = new GameObject();
				gameObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObject->GetTransform()->SetScale(Vector3(object->GetWidth()*scale.x, object->GetHeight()*scale.y, 1));
				gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
				gameObject->GetComponent<Collider>()->SetTrigger(true);
				gameObject->SetTag(objectGroup->GetName());
				gameObject->SetName(object->GetName());
				listAreas->push_back(gameObject);
			}
		}
		else if (objectGroup->GetName() == "Wall")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *gameObject = new GameObject();
				gameObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObject->GetTransform()->SetScale(Vector3(object->GetWidth()*scale.x, object->GetHeight()*scale.y, 1));
				gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
				gameObject->SetTag("Wall");
				gameObjectList->push_back(gameObject);
				thisQuad->Insert(gameObject);
			}
		}
		/*else if (objectGroup->GetName() == "Enemies")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *enemyObject = new GameObject();
				enemyObject->SetTag("Enemy");
				enemyObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObjectList->push_back(enemyObject);
				thisQuad->Insert(enemyObject);
			}
		}
		else if (objectGroup->GetName() == "Shuriken")
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *enemyObject = new GameObject();
				enemyObject->SetTag("Shuriken");
				enemyObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObjectList->push_back(enemyObject);
				thisQuad->Insert(enemyObject);
			}
		}*/
		else
		{
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *gameObject = new GameObject();
				gameObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObject->GetTransform()->SetScale(Vector3(object->GetWidth()*scale.x, object->GetHeight()*scale.y, 1));
				gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
				gameObject->SetTag(objectGroup->GetName());
				gameObject->SetName(object->GetName());
				gameObjectList->push_back(gameObject);
				thisQuad->Insert(gameObject);
			}
		}
	}
}

void DirectXCore::TileMap::Update()
{

}

void TileMap::Render()
{
	Vector3 worldToScreenShift = Vector3(mainCamera->GetWidth() / 2 - mainCamera->GetPosition().x, mainCamera->GetHeight() / 2 - mainCamera->GetPosition().y, 0);
	worldToScreenPosition = position + worldToScreenShift;
#pragma region OldTilemapAlgirithm
	//for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
	//{
	//	const Tmx::TileLayer *layer = tilemap->GetTileLayer(i);
	//	if (!layer->IsVisible()) continue;
	//	int tileDataWidth = tilemap->GetTileWidth();
	//	int tileDataHeight = tilemap->GetTileHeight();
	//	for (size_t m = 0; m < layer->GetHeight(); m++)
	//	{
	//		for (size_t n = 0; n < layer->GetWidth(); n++)
	//		{
	//			int tilesetIndex = layer->GetTileTilesetIndex(n, m);
	//			if (tilesetIndex != -1)
	//			{
	//				//tile index
	//				int tileID = layer->GetTileId(n, m);
	//				//Sprite* sprite = tilesetSheet[layer->GetTileTilesetIndex(n, m)];
	//				DirectX::SimpleMath::Vector3 currentPosition(((n * tileDataWidth) + tileDataWidth / 2), ((m * tileDataHeight) + tileDataHeight / 2), 0);
	//				currentPosition *= scale;
	//				currentPosition += worldToScreenPosition;
	//				if (mainCamera->IsContain(currentPosition, Vector3(tileDataWidth*scale.x, tileDataHeight*scale.y, 1))) {
	//					thisRenderer->SetRECT(*listTileID[tileID]);
	//					thisRenderer->Render(currentPosition, Vector3(0, 0, 0), scale);
	//				}
	//			}
	//		}
	//	}
	//}
#pragma endregion
#pragma region NewTilemapAlorithm
	for (int i = 0; i < data->size(); i++)
	{
		if (mainCamera->IsContain(positionList->at(i) + worldToScreenPosition, Vector3(16 * scale.x, 16 * scale.y, 1))) {
			if (listTileID[data->at(i)] != NULL)
			{
				thisRenderer->SetRECT(*listTileID[data->at(i)]);
				thisRenderer->Render(positionList->at(i) + worldToScreenPosition, Vector3(0, 0, 0), scale);
			}
		}
	}
#pragma endregion
}

void DirectXCore::TileMap::SetTilemapPosition(SimpleMath::Vector3 _tilemapPosition)
{
	position.x = _tilemapPosition.x;
	position.y = _tilemapPosition.y;
	position.z = _tilemapPosition.z;
}

void DirectXCore::TileMap::SetTilemapScale(SimpleMath::Vector3 _scale)
{
	scale.x = _scale.x;
	scale.y = _scale.y;
	scale.z = _scale.z;
}

TileMap::~TileMap()
{
}
