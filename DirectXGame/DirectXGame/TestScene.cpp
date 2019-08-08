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
	if (player->cutscene && enemySpawnList == NULL)
	{
		player->cutscene = false;
		enemySpawnList = new std::vector<GameObject*>();
		for (int i = 1; i < 4; i++)
		{
			Enemy* enemy = new Enemy(m_dxBase);
			enemy->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3((i * -100) - 300, -20, 0));
			enemy->AssignPlayer(player);
			Jumper* jumper = new Jumper(m_dxBase);
			jumper->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3((i * 100) + 300, -20, 0));
			jumper->AssignPlayer(player);
			dynamicGameObjectList->push_back(enemy);
			dynamicGameObjectList->push_back(jumper);
		}
		for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
		{
			if (dynamicGameObjectList->at(i)->GetTag() == "TriggerEnemy") this->DeleteObject(dynamicGameObjectList->at(i));
		}
	}

	gridTest->PreUpdate(elapsedTime);
	gridTest->Update(elapsedTime);
	gridTest->LateUpdate(elapsedTime);
	gameObjectList->clear();
	for (size_t i = 0; i < gridTest->GetAvailableGrids()->size(); i++) gameObjectList->insert(gameObjectList->end(), gridTest->GetAvailableGrids()->at(i)->objects.begin(), gridTest->GetAvailableGrids()->at(i)->objects.end());
	if (water != NULL) gameObjectList->push_back(water);
	if (trigger != NULL) gameObjectList->push_back(trigger);
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
	{
		dynamicGameObjectList->at(i)->PreUpdate(elapsedTime);
		if (dynamicGameObjectList->at(i)->GetComponent<Collider>() != NULL) dynamicGameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
	}
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
	}

	for (size_t i = 0; i < dynamicGameObjectList->size(); i++) dynamicGameObjectList->at(i)->Update(elapsedTime);
	for (size_t i = 0; i < dynamicGameObjectList->size(); i++) dynamicGameObjectList->at(i)->LateUpdate(elapsedTime);

	if(dynamicGameObjectList->size()<= enemynumbers)
	{
		Vector3 camPos = player->GetTransform()->GetPosition();
		if (camPos.y > 1000) camPos.y = 1000;
		if (camPos.x < 563) camPos.x = 563;
		camera->SetPosition(camPos);
	}
}

void TestScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
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
}

void TestScene::LoadScene()
{
	enemySpawnList = NULL;
	trigger = NULL;
	water = NULL;
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/NewMap/Charleston.BMP", L"Resources/00/NewMap/Charleston.txt", 20, 9, 128, 29, "Charleston");
	tilemap->SetCamera(camera);
	gridTest = new Grid(tilemap->GetMapSize(), 8, 8, tilemap->GetListGameObjects(), camera);
	gridTest->SetRenderer(tilemap->GetTilepRenderer());
	gridTest->AddRenderTile(tilemap->GetListTileIDs(), tilemap->GetData(), tilemap->GetPositionList(), tilemap->GetTilemapScale());

	player = new Player(m_dxBase);
	player->GetTransform()->SetPosition(Vector3(100, 800, 0));
	player->SetTag("Player");
	/*Enemy* enemy = new Enemy(m_dxBase);
	enemy->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3(200, -30, 0));
	enemy->AssignPlayer(player);*/
	/*Jumper* jumper = new Jumper(m_dxBase);
	jumper->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3(400, -30, 0));
	jumper->AssignPlayer(player);
	Shooter* shooter = new Shooter(m_dxBase);
	shooter->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector3(600, -30, 0));
	shooter->AssignPlayer(player);*/



	water = new GameObject();
	water->SetTag("Water");
	water->GetTransform()->SetPosition(Vector3(1032 * tilemap->GetTilemapScale().x, 472 * tilemap->GetTilemapScale().y - 50, 0));
	water->GetTransform()->SetScale(Vector3(2200 * tilemap->GetTilemapScale().x, 16 * tilemap->GetTilemapScale().y, 1));
	water->AddComponent<Collider>(new Collider(water, water->GetTransform()));
	trigger = new GameObject();
	trigger->SetTag("TriggerFirstBoss");
	trigger->GetTransform()->SetPosition(Vector3(5900, 1235, 0));
	trigger->GetTransform()->SetScale(Vector3(100, 100, 1));
	trigger->AddComponent<Collider>(new Collider(trigger, trigger->GetTransform()));
	GameObject* enemytrigger = new GameObject();
	enemytrigger->SetTag("TriggerEnemy");
	enemytrigger->GetTransform()->SetPosition(Vector3(1180, 1235, 0));
	enemytrigger->GetTransform()->SetScale(Vector3(50, 150, 1));
	enemytrigger->AddComponent<Collider>(new Collider(trigger, trigger->GetTransform()));


	dynamicGameObjectList->push_back(player);
	dynamicGameObjectList->push_back(player->GetShield());
	//dynamicGameObjectList->push_back(enemy);
	//dynamicGameObjectList->push_back(jumper);
	//dynamicGameObjectList->push_back(shooter);
	dynamicGameObjectList->push_back(enemytrigger);
	enemynumbers = dynamicGameObjectList->size();
}

void TestScene::UnloadScene()
{
}

TestScene::~TestScene()
{
}
