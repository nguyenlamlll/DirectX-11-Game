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
	//sprite->GetComponent<Animation>()->Update(0.001f);
	Rigidbody *rigidBody = sprite->GetComponent<Rigidbody>();
	if (rigidBody) if (!rigidBody->IsKinematic()) rigidBody->Move(SimpleMath::Vector3(0, 9.8f*rigidBody->GetMass().y, 0), 0.5f);
	Vector3 worldToScreenShift = Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 0);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		if (sprite != gameObjectList->at(i))
		{
			bool colType = sprite->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*sprite->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) collide = true;
		}
	}
	if (collide)
		if (sprite->GetComponent<Rigidbody>() != NULL) sprite->GetComponent<Rigidbody>()->SetKinematic(true);
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
	tilemap->Update();
	//camera->SetPosition(camera->GetPosition() + Vector3(2.f, 0, 0));
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), gameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	m_dxBase->CreateCamera(&camera);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/marioworld1-1.tmx");
	sprite = new Sprite(m_dxBase->GetDeviceResource(), L"Resources/rockman.png");
	tilemap->SetCamera(camera);
	sprite->GetTransform()->SetPosition(Vector3(100, 0, 0));
	sprite->AddComponent<Rigidbody>(new Rigidbody(sprite));
	sprite->AddComponent<Collider>(new Collider(sprite, sprite->GetTransform()));
	//sprite->AddComponent<Animation>(new Animation(sprite, 2, 8, 0.001f));
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	gameObjectList->insert(gameObjectList->end(), sprite);
}

void TilemapScene::UnloadScene()
{
}