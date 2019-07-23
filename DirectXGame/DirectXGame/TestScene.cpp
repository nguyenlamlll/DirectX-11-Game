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
	player->GetComponent<Collider>()->SetCollisionStatus(false);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (!gameObjectList->at(i)->GetComponent<Collider>()->IsTrigger())
		{
			float normalX, normalY;
			if (PhysicsManager::GetInstance()->CheckSweptAABB(player, gameObjectList->at(i), normalX, normalY) < 1.0f)
			{
				Vector3* normalVector = new Vector3(normalX, normalY, 0);
				player->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), *normalVector);
				player->GetComponent<Collider>()->SetCollisionStatus(true);
				//objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), *normalVector);
				//objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), *normalVector*-1);
			}
			/*Vector3 boundingboxCollisionCheck = PhysicsManager::GetInstance()->CheckBoundingBoxCollision(player, gameObjectList->at(i));
			if (boundingboxCollisionCheck.z == 1)
			{
				player->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), boundingboxCollisionCheck);
				player->GetComponent<Collider>()->SetCollisionStatus(true);
			}*/
		}
	}

	player->Update(elapsedTime);
	player->LateUpdate(elapsedTime);
	camera->SetPosition(player->GetTransform()->GetPosition());
	/*if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		camera->SetPosition(camera->GetPosition() + Vector3(5,0,0));*/
}

void TestScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	tilemap->Render();
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
	//gameObjectList = new std::vector<GameObject*>();
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Captain/Maps/Captain.tmx");
	//tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/Charleston_1_1.BMP", L"Resources/00/Charleston_1_1.CSV", 20, 4,128,30);
	tilemap->SetCamera(camera);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	box1 = new GameObject();
	box1->GetTransform()->SetPosition(Vector3(500, 200, 0));
	box1->GetTransform()->SetScale(Vector3(40, 40, 1));
	box1->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	box1->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/stand.png"));
	box1->AddComponent<Collider>(new Collider(box1, box1->GetTransform()));
	gameObjectList->push_back(box1);

	player = new Player(m_dxBase);
	player->SetTag("Player");
}


void TestScene::UnloadScene()
{
}

TestScene::~TestScene()
{
}
