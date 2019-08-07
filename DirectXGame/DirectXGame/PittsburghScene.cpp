#include "PittsburghScene.h"



PittsburghScene::PittsburghScene()
{
}

PittsburghScene::PittsburghScene(DxBase * _dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(_dxBase);
}

void PittsburghScene::UpdateScene(float elapsedTime)
{
	gameObjectList->clear();

	grid->PreUpdate(elapsedTime);
	grid->Update(elapsedTime);
	grid->LateUpdate(elapsedTime);

	gameObjectList->push_back(wall);
	for (size_t i = 0; i < grid->GetAvailableGrids()->size(); i++) gameObjectList->insert(gameObjectList->end(), grid->GetAvailableGrids()->at(i)->objects.begin(), grid->GetAvailableGrids()->at(i)->objects.end());
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
	camera->SetPosition(player->GetTransform()->GetPosition());
}

void PittsburghScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	if (tilemap != NULL)tilemap->Render();
	grid->Render();
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

void PittsburghScene::LoadScene()
{
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);

	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/Pittsburgh.BMP", L"Resources/00/Pittsburgh.CSV", 20, 7, 80, 60, "Pittsburgh");
	tilemap->SetCamera(camera);

	grid = new Grid(tilemap->GetMapSize(), 20, 20, tilemap->GetListGameObjects(), camera);
	grid->SetRenderer(tilemap->GetTilepRenderer());
	grid->AddRenderTile(tilemap->GetListTileIDs(), tilemap->GetData(), tilemap->GetPositionList(), tilemap->GetTilemapScale());

	player = new Player(m_dxBase);
	player->SetTag("Player");
	player->GetTransform()->SetPosition(Vector3(400, 200, 0));
	dynamicGameObjectList->push_back(player);
	dynamicGameObjectList->push_back(player->GetShield());

	//3400, 2700
	wall = new GameObject();
	wall->SetTag("Wall");
	wall->GetTransform()->SetPosition(Vector3(3400, 2760, 0));
	wall->GetTransform()->SetScale(Vector3(500, 20, 0));
	wall->AddComponent<Collider>(new Collider(wall,wall->GetTransform()));

	GameObject* trigger = new GameObject();
	trigger->SetTag("TriggerSecondBoss");
	trigger->GetTransform()->SetPosition(Vector3(3670, 2765, 0));
	trigger->GetTransform()->SetScale(Vector3(100, 100, 1));
	trigger->AddComponent<Collider>(new Collider(trigger, trigger->GetTransform()));
	dynamicGameObjectList->push_back(trigger);
}

void PittsburghScene::UnloadScene()
{
}


PittsburghScene::~PittsburghScene()
{
}
