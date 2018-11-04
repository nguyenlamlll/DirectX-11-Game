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
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (sprite != gameObjectList->at(i))
		{
			bool colType = sprite->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*sprite->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) collide = true;
		}
	}
	if (collide) {
		if(sprite->GetComponent<Rigidbody>()!=NULL) sprite->GetComponent<Rigidbody>()->SetKinematic(true);
	}
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
	tilemap->Update();
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	DirectX::SimpleMath::Vector3 worldToScreenPosition = DirectX::SimpleMath::Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 0);
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
	m_dxBase->CreateSprite(L"Resources/Rockman.png", &sprite);
	m_dxBase->CreateTilemap(L"Resources/marioworld1-1.tmx", &tilemap);
	tilemap->SetCamera(camera);
	sprite->GetTransform()->SetPosition(Vector3(0, 0, 0));
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	gameObjectList->insert(gameObjectList->end(),sprite);
	sprite->AddComponent<Rigidbody>(new Rigidbody(sprite));
	sprite->AddComponent<Collider>(new Collider(sprite, sprite->GetTransform()));
}

void TilemapScene::UnloadScene()
{
}