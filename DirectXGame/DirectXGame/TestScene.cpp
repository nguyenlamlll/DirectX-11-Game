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
	box1->PreUpdate(elapsedTime);

	float normalX, normalY;
	float contactTime = PhysicsManager::GetInstance()->CheckSweptAABB(player, box1, normalX, normalY);

	if (normalY < 0 && contactTime < 1)
	{
		bool a = PhysicsManager::GetInstance()->Collided(box1->GetComponent<Collider>()->GetCollider(), player->GetComponent<Collider>()->GetCollider());
		int asdasdasdasd = 1;
	}

	if ((normalY < 0 && contactTime < 1) || PhysicsManager::GetInstance()->Collided(box1->GetComponent<Collider>()->GetCollider(), player->GetComponent<Collider>()->GetCollider()))
	{
		Vector3 a = player->GetComponent<Rigidbody>()->GetVelocity();
		a.y = player->GetComponent<Rigidbody>()->GetVelocity().y*-1;
		player->GetComponent<Rigidbody>()->SetVelocity(player->GetComponent<Rigidbody>()->GetVelocity() + a);

		if (abs(player->GetComponent<Collider>()->GetColliderPosition().x - box1->GetComponent<Collider>()->GetColliderPosition().x) <= (player->GetComponent<Collider>()->GetColliderScale().x / 2 + box1->GetComponent<Collider>()->GetColliderScale().x / 2))
		{
			float j = abs(player->GetComponent<Collider>()->GetColliderPosition().y - box1->GetComponent<Collider>()->GetColliderPosition().y);
			float k = player->GetComponent<Collider>()->GetColliderScale().y/2 + box1->GetComponent<Collider>()->GetColliderScale().y/2;
			//player->GetComponent<Rigidbody>()->AddForce(player->GetComponent<Rigidbody>()->GetVelocity()*-1);
			if (box1->GetTransform()->GetPosition().y > player->GetTransform()->GetPosition().y)
			{
				if (player->GetComponent<Rigidbody>()->GetVelocity().y >= 0)
				{
					Vector3 a = player->GetComponent<Rigidbody>()->GetVelocity();
					a.y = player->GetComponent<Rigidbody>()->GetVelocity().y*-1;
					player->GetComponent<Rigidbody>()->SetVelocity(player->GetComponent<Rigidbody>()->GetVelocity() + a);
				}
			}
		}
	}

	player->Update(elapsedTime);
	player->LateUpdate(elapsedTime);
	box1->Update(elapsedTime);
	box1->LateUpdate(elapsedTime);

}

void TestScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	player->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	player->Render();

	box1->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	box1->Render();
}

void TestScene::LoadScene()
{
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);

	box1 = new GameObject();
	box1->GetTransform()->SetPosition(Vector3(500,200, 0));
	box1->GetTransform()->SetScale(Vector3(1000, 40, 1));
	box1->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	box1->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	box1->AddComponent<Collider>(new Collider(box1, box1->GetTransform()));

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
