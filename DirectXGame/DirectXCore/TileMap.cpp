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
	position.x = 0;
	position.y = 0;
	for (size_t i = 0; i < tilemap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = tilemap->GetTileset(i);

		std::string username = "Resources/" + tileset->GetImage()->GetSource();
		std::wstring wideusername;
		for (int i = 0; i < username.length(); ++i) wideusername += wchar_t(username[i]);
		const wchar_t* spritePath = wideusername.c_str();


		Sprite *tileSet = new Sprite(_deviceResource, spritePath);
		tilesetSheet.insert(std::pair<int, Sprite*>(i, tileSet));
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
					//world position = sprite local position + tilemap position
					tilesetSheet[layer->GetTileTilesetIndex(n, m)]->GetTransform()->SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
					tilesetSheet[layer->GetTileTilesetIndex(n, m)]->SetSpriteRect(sourceRECT);
					tilesetSheet[layer->GetTileTilesetIndex(n, m)]->GetTransform()->SetPosition(Vector3((n * tileDataWidth) + position.x, (m * tileDataHeight) + position.y, 0));
				}
			}
		}
	}
	for (size_t i = 0; i < tilemap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = tilemap->GetObjectGroup(i);

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			Tmx::Object *object = objectGroup->GetObjects().at(j);
			GameObject *gameObject = new GameObject();
			gameObject->GetTransform()->SetPosition(position + Vector3(object->GetX(), object->GetY(), 0));
			gameObject->GetTransform()->SetScale(Vector3(object->GetWidth(), object->GetHeight(), 1));
			gameObject->AddComponent<Collider>(new Collider(gameObject, gameObject->GetTransform()));
			//gameObject->GetComponent<Collider>()->SetColliderScale(Vector3(object->GetWidth(), object->GetHeight(), 1));
			gameObjectList->push_back(gameObject);
		}
	}
}

void DirectXCore::TileMap::Update()
{
	/*DirectX::SimpleMath::Vector3 trans = DirectX::SimpleMath::Vector3(deviceResource->GetOutputSize().right / 2 - mainCamera->GetPosition().x,
		deviceResource->GetOutputSize().bottom / 2 - mainCamera->GetPosition().y);*/
		//position += DirectX::SimpleMath::Vector3(2.f,0);
		//mainCamera->SetPosition(mainCamera->GetPosition() + DirectX::SimpleMath::Vector3(3.f, 0,0));
}

void TileMap::Render()
{
	DirectX::SimpleMath::Vector3 worldToScreenPosition = DirectX::SimpleMath::Vector3(mainCamera->GetBound().right / 2 - mainCamera->GetPosition().x, mainCamera->GetBound().bottom / 2 - mainCamera->GetPosition().y, 1);
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

					//world position = sprite local position + tilemap position
					Sprite* sprite = tilesetSheet[layer->GetTileTilesetIndex(n, m)];
					DirectX::SimpleMath::Vector3 currentPosition((n * tileDataWidth) + position.x, (m * tileDataHeight) + position.y, 1);
					sprite->SetSpriteRect(listTileID[tileID]);
					sprite->GetTransform()->SetPosition(currentPosition);
					if (mainCamera->IsContain(sprite->GetTransform()->GetWorldToCameraPosition(worldToScreenPosition), sprite->GetWorldToScreenScale()))
					{
						sprite->Render(sprite->GetTransform()->GetWorldToCameraPosition(worldToScreenPosition));
					}
				}
			}
		}
	}

}


TileMap::~TileMap()
{
}
