#include "stdafx.h"
#include "TileMap.h"


TileMap::TileMap()
{
}

TileMap::TileMap(DirectXCore::DeviceResources *_deviceResource, const wchar_t * path)
{
	deviceResource = _deviceResource;
	tilemap = new Tmx::Map;

	std::wstring ws(path);
	std::string pathstr(ws.begin(), ws.end());

	tilemap->ParseFile(pathstr);
	RECT *r = new RECT();
	r->left = r->right = 0;
	r->right = tilemap->GetWidth()*tilemap->GetTileWidth();
	r->bottom = tilemap->GetHeight()*tilemap->GetTileHeight();

	for (size_t i = 0; i < tilemap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = tilemap->GetTileset(i);

		/*std::string str = tileset->GetImage()->GetSource();
		const wchar_t* widecstr = str.c_str();*/

		std::string username = "Resources/" + tileset->GetImage()->GetSource();
		std::wstring wideusername;
		for (int i = 0; i < username.length(); ++i) wideusername += wchar_t(username[i]);
		const wchar_t* your_result = wideusername.c_str();


		Sprite *sprite = new Sprite(_deviceResource, your_result);
		listTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}

	m_screenPos.x = _deviceResource->GetOutputSize().right / 2;
	m_screenPos.y = _deviceResource->GetOutputSize().bottom / 2;
}

void TileMap::Render()
{
	DirectX::SimpleMath::Vector2 trans = DirectX::SimpleMath::Vector2(deviceResource->GetOutputSize().right / 2 - mainCamera->GetPosition().x,
																    	deviceResource->GetOutputSize().bottom / 2 - mainCamera->GetPosition().y);

	for (int i = 0; i < tilemap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = tilemap->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		RECT sourceRECT;

		int tileDataWidth = tilemap->GetTileWidth();
		int tileDataHeight = tilemap->GetTileHeight();

		for (size_t m = 0; m < layer->GetHeight(); m++)
		{
			for (size_t n = 0; n < layer->GetWidth(); n++)
			{
				int tilesetIndex = layer->GetTileTilesetIndex(n, m);

				if (tilesetIndex != -1)
				{
					const Tmx::Tileset *tileSet = tilemap->GetTileset(tilesetIndex);
					int tileSetHorizontalCount = tileSet->GetImage()->GetWidth() / tileDataWidth;
					int tileSetVerticalCount = tileSet->GetImage()->GetHeight() / tileDataHeight;

					Sprite* sprite = listTileset[layer->GetTileTilesetIndex(n, m)];

					//tile index
					int tileID = layer->GetTileId(n, m);
					int dataYIndex = tileID / tileSetHorizontalCount;
					int dataXIndex = tileID % tileSetHorizontalCount;

					sourceRECT.top = dataYIndex * tileDataHeight;
					sourceRECT.bottom = sourceRECT.top + tileDataHeight;
					sourceRECT.left = dataXIndex * tileDataWidth;
					sourceRECT.right = sourceRECT.left + tileDataWidth;

					//world position = sprite local position + tilemap position
					DirectX::XMFLOAT2 position((n * tileDataWidth + tileDataWidth / 2) + m_screenPos.x, (m * tileDataHeight + tileDataHeight / 2) + m_screenPos.y);
					DirectX::SimpleMath::Vector2* newCenter = new DirectX::SimpleMath::Vector2(tileDataWidth / 2, tileDataHeight / 2);

					sprite->SetCenter(*newCenter);
					sprite->SetScale(1.0f, 1.0f);
					sprite->SetScreenPosition(position);
					sprite->SetSpriteRect(sourceRECT);
					sprite->RenderSprite();
				}
			}
		}
	}

}


TileMap::~TileMap()
{
}
