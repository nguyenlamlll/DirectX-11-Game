#include "stdafx.h"
#include "TileMap.h"

using namespace DirectXCore;

TileMap::TileMap()
{
}

TileMap::TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t * path)
{
	gameObjectList = new std::vector<GameObject*>();
	deviceResource = _deviceResource;
	tilemap = new Tmx::Map;
	std::wstring ws(path);
	std::string pathstr(ws.begin(), ws.end());
	tilemap->ParseFile(pathstr);
	position = Vector3(0, 0, 0);
	scale = Vector3(2, 2, 1);
	worldToScreenPosition = position;

	RECT* newRegion = new RECT();
	newRegion->left = newRegion->top = 0;
	newRegion->right = tilemap->GetWidth()*tilemap->GetTileWidth()*scale.x;
	newRegion->bottom = tilemap->GetHeight()*tilemap->GetTileHeight()*scale.y;

	thisQuad = new QuadTree(newRegion, 1, 2);

	for (size_t i = 0; i < tilemap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = tilemap->GetTileset(i);
		int as = tileset->GetTileWidth();
		std::string username = "Resources/" + tileset->GetImage()->GetSource();// old tilemap
		//std::string username = "Resources/" + tileset->GetImageInTileset()->GetSource();// new tilemap
		std::wstring wideusername;
		for (int i = 0; i < username.length(); ++i) wideusername += wchar_t(username[i]);
		const wchar_t* spritePath = wideusername.c_str();

		thisRenderer = new Renderer(_deviceResource, spritePath);
		thisRenderer->SetPivot(Vector3(tileset->GetTileWidth() / 2, tileset->GetTileHeight() / 2, 0));
		GameObject* renderingThing = new GameObject();
		renderingThing->AddComponent<Renderer>(new Renderer(_deviceResource, spritePath));
		renderingThing->GetTransform()->SetScreenScale(scale);
		renderingThing->GetTransform()->SetScale(Vector3(tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight(), 1));// old tilemap
		//renderingThing->GetTransform()->SetScale(Vector3(tileset->GetImageInTileset()->GetWidth(),tileset->GetImageInTileset()->GetHeight(),1)); // new tilemap
		listRenderers.push_back(renderingThing);
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
		else if (objectGroup->GetName() == "Stage")
		{

		}
		else if(objectGroup->GetName() == "Wall") {
			for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
			{
				Tmx::Object *object = objectGroup->GetObjects().at(j);
				GameObject *gameObject = new GameObject();
				gameObject->GetTransform()->SetPosition((position + Vector3(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2, 0))*scale);
				gameObject->GetTransform()->SetScale(Vector3(object->GetWidth()*scale.x, object->GetHeight()*scale.y, 1));
				gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
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
	Vector3 worldToScreenShift = Vector3(
		mainCamera->GetWidth() / 2 - mainCamera->GetPosition().x,
		mainCamera->GetHeight() / 2 - mainCamera->GetPosition().y,
		0);
	worldToScreenPosition = position + worldToScreenShift;

#pragma region OldTilemapAlgirithm
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
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);
				if (tilesetIndex != -1)
				{
					//tile index
					int tileID = layer->GetTileId(n, m);
					//Sprite* sprite = tilesetSheet[layer->GetTileTilesetIndex(n, m)];
					DirectX::SimpleMath::Vector3 currentPosition(((n * tileDataWidth) + tileDataWidth / 2), ((m * tileDataHeight) + tileDataHeight / 2), 0);
					currentPosition *= scale;
					currentPosition += worldToScreenPosition;
					if (mainCamera->IsContain(currentPosition, Vector3(tileDataWidth*scale.x, tileDataHeight*scale.y, 1))) {
						thisRenderer->SetRECT(*listTileID[tileID]);
						thisRenderer->Render(currentPosition, Vector3(0, 0, 0), scale);
					}
					if (m == 30 && n == 0)
						SimpleMath::Vector3 pl = currentPosition;
				}
			}
		}
	}
#pragma endregion

#pragma region NewTilemapAlgorithm
	/*for (int n = 0; n < listRenderers.size(); n++) {
		listRenderers.at(n)->GetTransform()->SetWorldToScreenPosition(worldToScreenPosition);
		listRenderers.at(n)->Render();
	}*/
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
