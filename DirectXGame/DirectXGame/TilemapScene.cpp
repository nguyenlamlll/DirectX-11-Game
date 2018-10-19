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
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		bool colType = sprite->GetBoxCollider()->Intersects(*gameObjectList->at(i)->GetBoxCollider());
		bool colType2 = gameObjectList->at(i)->GetBoxCollider()->Intersects(*sprite->GetBoxCollider()); 
		if (colType || colType2)
			collide = true;
	}
	//if (!collide) sprite->GetTransform()->SetPosition(sprite->GetTransform()->GetPosition() + Vector3(0, 4.f, 0));
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	DirectX::SimpleMath::Vector3 worldToScreenPosition = DirectX::SimpleMath::Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 1);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToCameraPosition(worldToScreenPosition), gameObjectList->at(i)->GetTransform()->GetScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	m_dxBase->CreateCamera(&camera);
	m_dxBase->CreateSprite(L"cat.png", &sprite);
	m_dxBase->CreateTilemap(L"Resources/marioworld1-1.tmx", &tilemap);
	tilemap->SetCamera(camera);
	sprite->GetTransform()->SetPosition(Vector3(0, 0, 1));
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	gameObjectList->insert(gameObjectList->end(),sprite);
}

void TilemapScene::UnloadScene()
{
}