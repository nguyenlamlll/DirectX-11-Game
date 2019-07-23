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
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->PreUpdate(elapsedTime);
	}
	//PHYSICS
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		//if (gameObjectList->at(i) != player)
		//{
		//	if (!gameObjectList->at(i)->GetComponent<Collider>()->IsTrigger())
		//	{
		//		float normalX, normalY;
		//		if (PhysicsManager::GetInstance()->CheckSweptAABB(player, gameObjectList->at(i), normalX, normalY) < 1.0f)
		//		{
		//			Vector3* normalVector = new Vector3(normalX, normalY, 0);
		//			player->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), *normalVector);
		//			player->GetComponent<Collider>()->SetCollisionStatus(true);
		//			//objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), *normalVector);
		//			//objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), *normalVector*-1);
		//		}
		//	}
		//}
		for (size_t j = 0; j < gameObjectList->size(); j++)
		{
			if (gameObjectList->at(i) != gameObjectList->at(j))
			{
				if (gameObjectList->at(i)->GetComponent<Collider>() != NULL && gameObjectList->at(j)->GetComponent<Collider>() != NULL)
				{
					if (!gameObjectList->at(i)->GetComponent<Collider>()->IsTrigger() && !gameObjectList->at(j)->GetComponent<Collider>()->IsTrigger())
					{
						float normalX, normalY;
						if (PhysicsManager::GetInstance()->CheckSweptAABB(gameObjectList->at(i), gameObjectList->at(j), normalX, normalY) < 1.0f)
						{
							Vector3* normalVector = new Vector3(normalX, normalY, 0);
							gameObjectList->at(i)->OnCollisionEnter(gameObjectList->at(j)->GetComponent<Collider>(), *normalVector);
							gameObjectList->at(j)->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), *normalVector*-1);
							gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(true);
							gameObjectList->at(j)->GetComponent<Collider>()->SetCollisionStatus(true);
						}
					}
				}
			}
		}
	}
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->Update(elapsedTime);
	}
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->LateUpdate(elapsedTime);
	}
	camera->SetPosition(player->GetTransform()->GetPosition());
}

void TestScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		std::vector<GameObject*>* childrens = gameObjectList->at(i)->GetChildrens();
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), gameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			gameObjectList->at(i)->Render();
		}
		for (size_t k = 0; k < childrens->size(); k++)
		{
			childrens->at(k)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
			if (camera->IsContain(childrens->at(k)->GetTransform()->GetWorldToScreenPosition(), childrens->at(k)->GetTransform()->GetScreenScale()))
			{
				childrens->at(k)->Render();
			}
		}
	}
}

void TestScene::LoadScene()
{
	player = new Player(m_dxBase);
	player->SetTag("Player");
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Captain/Maps/Captain.tmx");
	//tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/Charleston_1_1.BMP", L"Resources/00/Charleston_1_1.CSV", 20, 4,128,30);
	tilemap->SetCamera(camera);
	gameObjectList->push_back(player);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());

	Enemy* enemy = new Enemy(m_dxBase);
	enemy->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3(-70, -50, 0));
	enemy->AssignPlayer(player);
	gameObjectList->push_back(enemy);
}


void TestScene::UnloadScene()
{
}

TestScene::~TestScene()
{
}
