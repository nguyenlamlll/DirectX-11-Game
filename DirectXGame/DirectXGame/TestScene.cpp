#include "TestScene.h"



TestScene::TestScene()
{
}

TestScene::TestScene(DirectXCore::DxBase * dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

void TestScene::UpdateScene(float elapsedTime)
{
	player->PreUpdate(elapsedTime);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		float normalX, normalY;
		if (PhysicsManager::GetInstance()->CheckSweptAABB(player, gameObjectList->at(i), normalX, normalY) < 1.0f)
		{
			Vector3* normalVector = new Vector3(normalX, normalY, 0);
			player->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), *normalVector);
			//objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), *normalVector);
			//objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), *normalVector*-1);
		}
	}


	player->Update(elapsedTime);
	player->LateUpdate(elapsedTime);
	camera->SetPosition(player->GetTransform()->GetPosition());
}

void TestScene::RenderScene()
{
	tilemap->Render();
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	player->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	player->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), gameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
}

void TestScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Captain/Maps/Captain.tmx");
	tilemap->SetCamera(camera);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	box1 = new GameObject();
	box1->GetTransform()->SetPosition(Vector3(500,200, 0));
	box1->GetTransform()->SetScale(Vector3(40, 40, 1));
	box1->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	box1->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	box1->AddComponent<Collider>(new Collider(box1, box1->GetTransform()));
	gameObjectList->push_back(box1);

	player = new Player(m_dxBase);
	player->SetTag("Player");
	//camera->SetPosition(player->GetTransform()->GetPosition());
}


void TestScene::UnloadScene()
{
}

TestScene::~TestScene()
{
}
