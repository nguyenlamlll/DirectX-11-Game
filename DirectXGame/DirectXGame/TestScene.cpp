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
	gridTest->PreUpdate(elapsedTime);
	gridTest->Update(elapsedTime);
	gridTest->LateUpdate(elapsedTime);
	gameObjectList->clear();
	for (size_t i = 0; i < gridTest->GetAvailableGrids()->size(); i++)
	{
		if (i != 0) break;
		gameObjectList->insert(gameObjectList->end(), gridTest->GetAvailableGrids()->at(i)->objects.begin(), gridTest->GetAvailableGrids()->at(i)->objects.end());
	}


	////PRE UPDATE
	//for (size_t i = 0; i < gameObjectList->size(); i++)
	//{
	//	gameObjectList->at(i)->PreUpdate(elapsedTime);
	//	if (gameObjectList->at(i)->GetComponent<Collider>() != NULL) gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
	//}
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
	{
		dynamicGameObjectList->at(i)->PreUpdate(elapsedTime);
		if (dynamicGameObjectList->at(i)->GetComponent<Collider>() != NULL) dynamicGameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
	}
	//PHYSICS
	gameObjectList->insert(gameObjectList->end(), dynamicGameObjectList->begin(), dynamicGameObjectList->end());
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		for (size_t j = 0; j < dynamicGameObjectList->size(); j++)
		{
			if (gameObjectList->at(i) != dynamicGameObjectList->at(j))
			{
				if (gameObjectList->at(i)->GetComponent<Collider>() != NULL && dynamicGameObjectList->at(j)->GetComponent<Collider>() != NULL)
				{
					if (!gameObjectList->at(i)->GetComponent<Collider>()->IsTrigger() && !dynamicGameObjectList->at(j)->GetComponent<Collider>()->IsTrigger())
					{
						float normalX, normalY;
						if (PhysicsManager::GetInstance()->CheckSweptAABB(dynamicGameObjectList->at(j), gameObjectList->at(i), normalX, normalY) < 1.0f)
						{
							Vector3* normalVector = new Vector3(normalX, normalY, 0);
							gameObjectList->at(i)->OnCollisionEnter(gameObjectList->at(j)->GetComponent<Collider>(), *normalVector*-1);
							dynamicGameObjectList->at(j)->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), *normalVector);
							gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(true);
							dynamicGameObjectList->at(j)->GetComponent<Collider>()->SetCollisionStatus(true);
						}
					}
				}
			}
		}

		/*for (size_t j = 0; j < gameObjectList->size(); j++)
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
		}*/
	}
	////UPDATE
	//for (size_t i = 0; i < gameObjectList->size(); i++)
	//{
	//	gameObjectList->at(i)->Update(elapsedTime);
	//}
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
	{
		dynamicGameObjectList->at(i)->Update(elapsedTime);
	}
	////LATE UPDATE
	//for (size_t i = 0; i < gameObjectList->size(); i++)
	//{
	//	gameObjectList->at(i)->LateUpdate(elapsedTime);
	//}
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
	{
		dynamicGameObjectList->at(i)->LateUpdate(elapsedTime);
	}

	camera->SetPosition(player->GetTransform()->GetPosition());
}

void TestScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	//tilemap->Render();
	gridTest->Render();
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
	{
		dynamicGameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		std::vector<GameObject*>* childrens = dynamicGameObjectList->at(i)->GetChildrens();
		if (camera->IsContain(dynamicGameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), dynamicGameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			dynamicGameObjectList->at(i)->Render();
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
	/*for (size_t i = 0; i < gameObjectList->size(); i++)
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
	}*/
}

void TestScene::LoadScene()
{
	player = new Player(m_dxBase);
	player->SetTag("Player");
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	//tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Captain/Maps/Captain.tmx");
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/Charleston_1_1.BMP", L"Resources/00/Charleston_1_1.CSV", 20, 4, 128, 30);
	tilemap->SetCamera(camera);
	gameObjectList->push_back(player);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());

	gridTest = new Grid(tilemap->GetMapSize(), 2, 8, tilemap->GetListGameObjects(), camera);
	gridTest->SetRenderer(tilemap->GetTilepRenderer());
	gridTest->AddRenderTile(tilemap->GetListTileIDs(), tilemap->GetData(), tilemap->GetPositionList(), tilemap->GetTilemapScale());

	Enemy* enemy = new Enemy(m_dxBase);
	enemy->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3(50, -30, 0));
	enemy->AssignPlayer(player);
	dynamicGameObjectList->push_back(player);
	dynamicGameObjectList->push_back(enemy);

	//WizardBoss* boss = new WizardBoss(m_dxBase,player);
	//gameObjectList->push_back(boss);
}


void TestScene::UnloadScene()
{
}

TestScene::~TestScene()
{
}
