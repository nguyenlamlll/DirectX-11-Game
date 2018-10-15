#include "TilemapScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector2;

TilemapScene::TilemapScene(DxBase* dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

TilemapScene::~TilemapScene()
{
}

void TilemapScene::UpdateScene(float elapsedTime)
{
	tilemap->Update();
	sprite->Update();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		bool colType = sprite->GetBoxCollider()->Intersects(*gameObjectList->at(i)->GetBoxCollider());
		bool colType2 = gameObjectList->at(i)->GetBoxCollider()->Intersects(*sprite->GetBoxCollider()); 
		if (colType || colType2)
			collide = true;
	}
	if (!collide) sprite->GetTransform()->SetPosition(sprite->GetTransform()->GetPosition() + Vector3(0, 4.f, 0));
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	sprite->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	m_dxBase->CreateSprite(L"cat.png", &sprite);
	sprite->GetTransform()->SetPosition(Vector3(100, 0, 1));
	m_dxBase->CreateTilemap(L"Resources/marioworld1-1.tmx", &tilemap);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	//mainCamera = new Camera(m_deviceResources->GetOutputSize().right / 2, m_deviceResources->GetOutputSize().bottom);
	//tilemap = new TileMap(, L"Resources/untitled.tmx");
	//tilemap->SetCamera(mainCamera);
	int a = 0;
}

void TilemapScene::UnloadScene()
{
}