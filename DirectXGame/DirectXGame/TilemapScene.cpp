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
	Vector3 worldToScreenShift = Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 0);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToCameraPosition(worldToScreenShift);
		if (sprite != gameObjectList->at(i))
		{
			bool colType = sprite->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*sprite->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) collide = true;
		}
	}
	if (collide) {
		if (sprite->GetComponent<Rigidbody>() != NULL) sprite->GetComponent<Rigidbody>()->SetKinematic(true);
	}
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
	tilemap->Update();

	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
	{
		sprite->GetTransform()->SetPosition(sprite->GetTransform()->GetPosition() + Vector3(3.f, 0, 0));
		camera->SetPosition(camera->GetPosition() + Vector3(6.f, 0, 0));
	}
	else
	{
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		sprite->GetTransform()->SetPosition(sprite->GetTransform()->GetPosition() + Vector3(-3.f, 0, 0));
		camera->SetPosition(camera->GetPosition() + Vector3(-6.f, 0, 0));
	}
	else
	{
	}

	if (m_dxBase->GetInputManager()->IsKeyDown("J"))
	{
		//Sprite* bullet;
		//m_dxBase->CreateSprite(L"Resources/Weapons/SingleShot.png", &bullet);
		//auto characterPosition = sprite->GetTransform()->GetPosition();
		//bullet->GetTransform()->SetPosition(Vector3(400.f, 100.f, 0));
		//bulletSprites.push_back(bullet);
	}
	for (size_t i = 0; i < bulletSprites.size(); i++)
	{
		/*bulletSprites.at(i)->GetTransform()->SetPosition(bulletSprites.at(i)->GetTransform()->GetPosition() + Vector3(2.f, 0, 0));*/
	}
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToCameraPosition(), gameObjectList->at(i)->GetTransform()->GetScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	m_dxBase->CreateCamera(&camera);
	//m_dxBase->CreateSprite(L"Resources/Rockman.png", &sprite);
	//tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Resources/marioworld1-1.tmx");

	m_dxBase->CreateSprite(L"Resources/Rockman.png", &sprite);
	//sprite = new Sprite(m_dxBase->GetDeviceResource(), L"Resources/Rockman.png");
	m_dxBase->CreateTilemap(L"Resources/marioworld1-1.tmx", &tilemap);
	tilemap->SetCamera(camera);
	sprite->GetTransform()->SetPosition(Vector3(100, 0, 0));
	sprite->AddComponent<Rigidbody>(new Rigidbody(sprite));
	sprite->AddComponent<Collider>(new Collider(sprite, sprite->GetTransform()));
	sprite->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Rockman.png", sprite));
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	gameObjectList->insert(gameObjectList->end(), sprite);

	bulletSprites = std::vector<Sprite*>();

	m_dxBase->CreateSoundAndMusic(L"Resources/Music/10 Blizzard Buffalo.wav", &m_backgroundMusic);
	m_backgroundMusic->Play();
}

void TilemapScene::UnloadScene()
{
}