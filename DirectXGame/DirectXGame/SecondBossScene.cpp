#include "SecondBossScene.h"



SecondBossScene::SecondBossScene()
{
}

SecondBossScene::SecondBossScene(DxBase * _dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(_dxBase);
}

void SecondBossScene::UpdateScene(float elapsedTime)
{
	gameObjectList->clear();
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
	//camera->SetPosition(player->GetTransform()->GetPosition());
}

void SecondBossScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
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

void SecondBossScene::LoadScene()
{
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);

	Player* player = new Player(m_dxBase);
	player->SetTag("Player");
	player->GetTransform()->SetPosition(Vector3(100, 100, 0));

	GameObject* wall = new GameObject();
	wall->SetTag("Wall");
	wall->GetTransform()->SetPosition(Vector3(512, 650, 0));
	wall->GetTransform()->SetScale(Vector3(10000, 100, 1));
	wall->AddComponent<Collider>(new Collider(wall, wall->GetTransform()));

	background = new GameObject();
	background->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/00/NewMap/SecondBossMap.png"));
	background->GetTransform()->SetPosition(camera->GetPosition());
	background->GetTransform()->SetScreenScale(Vector3(2.6f, 2.4f, 1));

	SecondBoss* secondboss = new SecondBoss(m_dxBase,player);

	dynamicGameObjectList->push_back(background);
	dynamicGameObjectList->push_back(wall);
	dynamicGameObjectList->push_back(player);
	dynamicGameObjectList->push_back(player->GetShield());
	dynamicGameObjectList->push_back(secondboss);
}

void SecondBossScene::UnloadScene()
{
}


SecondBossScene::~SecondBossScene()
{
}
