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
	//box1->PreUpdate(elapsedTime);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		float normalX, normalY;
		float contactTime = PhysicsManager::GetInstance()->CheckSweptAABB(player, gameObjectList->at(i), normalX, normalY);
		if (normalY < 0 && contactTime < 1)
		{
			if (normalY < 0 && contactTime < 1)
			{
				Vector3 a = player->GetComponent<Rigidbody>()->GetVelocity();
				Vector3 b = player->GetComponent<Rigidbody>()->GetVelocity() + a * -1;
				a.y = player->GetComponent<Rigidbody>()->GetVelocity().y*-1;
				player->GetComponent<Rigidbody>()->SetVelocity(player->GetComponent<Rigidbody>()->GetVelocity() + a);
			}
		}
	}

	
	player->Update(elapsedTime);
	player->LateUpdate(elapsedTime);
	//box1->Update(elapsedTime);
	//box1->LateUpdate(elapsedTime);
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
	/*box1->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	box1->Render();*/
}

void TestScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/Captain/Maps/Captain.tmx");
	tilemap->SetCamera(camera);
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	/*box1 = new GameObject();
	box1->GetTransform()->SetPosition(Vector3(500,200, 0));
	box1->GetTransform()->SetScale(Vector3(1000, 40, 1));
	box1->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	box1->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	box1->AddComponent<Collider>(new Collider(box1, box1->GetTransform()));*/

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
