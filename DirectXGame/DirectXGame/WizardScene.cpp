#include "WizardScene.h"



WizardScene::WizardScene()
{
}

WizardScene::WizardScene(DxBase* _dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(_dxBase);
}

void WizardScene::UpdateScene(float elapsedTime)
{
	gameObjectList->clear();

	mapGrid->PreUpdate(elapsedTime);
	mapGrid->Update(elapsedTime);
	mapGrid->LateUpdate(elapsedTime);
	for (size_t i = 0; i < mapGrid->GetAvailableGrids()->size(); i++) gameObjectList->insert(gameObjectList->end(), mapGrid->GetAvailableGrids()->at(i)->objects.begin(), mapGrid->GetAvailableGrids()->at(i)->objects.end());
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
}

void WizardScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	if (bossTilemap != NULL)bossTilemap->Render();
	mapGrid->Render();
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

void WizardScene::LoadScene()
{
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);

	bossTilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/00/NewMap/CharlestonBoss.BMP", L"Resources/00/NewMap/CharlestonBoss.txt", 20, 2, 16, 14, "CharlestonBoss");
	bossTilemap->SetCamera(camera);

	mapGrid = new Grid(bossTilemap->GetMapSize(), 2, 8, bossTilemap->GetListGameObjects(), camera);
	mapGrid->SetRenderer(bossTilemap->GetTilepRenderer());
	mapGrid->AddRenderTile(bossTilemap->GetListTileIDs(), bossTilemap->GetData(), bossTilemap->GetPositionList(), bossTilemap->GetTilemapScale());

	player = new Player(m_dxBase);
	player->SetTag("Player");
	player->GetTransform()->SetPosition(Vector3(400, 200, 0));
	WizardBoss* boss = new WizardBoss(m_dxBase, player);
	dynamicGameObjectList->push_back(player);
	dynamicGameObjectList->push_back(player->GetShield());
	dynamicGameObjectList->push_back(boss);
}

void WizardScene::UnloadScene()
{
}

WizardScene::~WizardScene()
{
}
