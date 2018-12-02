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
	position.z = 0;
	worldToScreenPosition = position;

	for (size_t i = 0; i < tilemap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = tilemap->GetTileset(i);
		int as= tileset->GetTileWidth();
		std::string username = "Resources/" + tileset->GetImageInTileset()->GetSource();
		std::wstring wideusername;
		for (int i = 0; i < username.length(); ++i) wideusername += wchar_t(username[i]);
		const wchar_t* spritePath = wideusername.c_str();


		Sprite *tileSet = new Sprite(_deviceResource, spritePath);
		tilesetSheet.insert(std::pair<int, Sprite*>(i, tileSet));
		//tileSet->AddComponent<Renderer>(new Renderer(_deviceResource,spritePath));
		thisRenderer = new Renderer(_deviceResource, spritePath);
		GameObject* renderingThing = new GameObject();
		renderingThing->AddComponent<Renderer>(new Renderer(_deviceResource, spritePath));
		renderingThing->GetTransform()->SetScreenScale(Vector3(tileset->GetImageInTileset()->GetWidth(),tileset->GetImageInTileset()->GetHeight(),0));
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
				listRenderers.at(j)->GetTransform()->SetPosition(Vector3(object->GetX(),object->GetY(),0));
			}
		}
		else {
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
}

void DirectXCore::TileMap::Update()
{

}

void TileMap::Render()
{
	Vector3 worldToScreenShift = Vector3(
		mainCamera->GetBound().right / 2 - mainCamera->GetPosition().x, 
		mainCamera->GetBound().bottom / 2 - mainCamera->GetPosition().y, 
		0);
	worldToScreenPosition = position + worldToScreenShift;

//	for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
//	{
//		const Tmx::TileLayer *layer = tilemap->GetTileLayer(i);
//		if (!layer->IsVisible()) continue;
//		int tileDataWidth = tilemap->GetTileWidth();
//		int tileDataHeight = tilemap->GetTileHeight();
//		for (size_t m = 0; m < layer->GetHeight(); m++)
//		{
//			for (size_t n = 0; n < layer->GetWidth(); n++)
//			{
//				int tilesetIndex = layer->GetTileTilesetIndex(n, m);
//				if (tilesetIndex != -1)
//				{
//					//tile index
//					int tileID = layer->GetTileId(n, m);
//
//					Sprite* sprite = tilesetSheet[layer->GetTileTilesetIndex(n, m)];
//					DirectX::SimpleMath::Vector3 currentPosition((n * tileDataWidth) + worldToScreenPosition.x, (m * tileDataHeight) + worldToScreenPosition.y, 1);
//					if (mainCamera->IsContain(currentPosition, Vector3(32, 32, 1))) {
//						thisRenderer->SetRECT(*listTileID[tileID]);
//						thisRenderer->Render(currentPosition);
//					}
////					if (mainCamera->IsContain(currentPosition, sprite->GetTransform()->GetScreenScale()))
////					{
////						thisRenderer->SetRECT(*listTileID[tileID]);
////						thisRenderer->Render(currentPosition);
////						/*sprite->GetComponent<Renderer>()->SetRECT(*listTileID[tileID]);
////						sprite->GetComponent<Renderer>()->Render(currentPosition);*/
////					}
////#if defined(DEBUG) | defined(_DEBUG)
////					else
////					{
////						int placeBreakPointHereToCheckIfCameraIsWorking = 0;
////					}
////#endif
//				}
//			}
//		}
//	}


	for (int n = 0; n < listRenderers.size(); n++) {
		listRenderers.at(n)->GetTransform()->SetWorldToScreenPosition(worldToScreenPosition);
		listRenderers.at(n)->Render();
	}
}


TileMap::~TileMap()
{
}
