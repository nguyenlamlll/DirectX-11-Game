#include "TilemapScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector2;

TilemapScene::TilemapScene(DxBase* dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

TilemapScene::~TilemapScene()
{
}

void TilemapScene::UpdateScene(float elapsedTime)
{
	Vector3 worldToScreenShift = Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 0);
	newGameObject->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	newGameObject->GetComponent<Animation>()->Update(0.11f);
	newGameObject->GetComponent<Collider>()->SetColliderScale(Vector3(46, 46, 1));
	newGameObject->GetComponent<Collider>()->SetColliderPosition(newGameObject->GetTransform()->GetPosition());
	//sprite->GetComponent<Animation>()->Update(0.001f);
	Rigidbody *rigidBody = newGameObject->GetComponent<Rigidbody>();
	if (rigidBody)
		if (!rigidBody->IsKinematic()) 
			rigidBody->Move(SimpleMath::Vector3(0, 9.8f*rigidBody->GetMass().y, 0), 0.5f);
		else
			rigidBody->Move(SimpleMath::Vector3(0, 0.f*rigidBody->GetMass().y, 0), 0.5f);
	newGameObject->GetTransform()->SetPosition(newGameObject->GetTransform()->GetPosition() + rigidBody->GetVelocity());
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		if (newGameObject != gameObjectList->at(i))
		{
			bool colType = newGameObject->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*newGameObject->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) collide = true;
		}
	}
	if (collide && first) {
		if (newGameObject->GetComponent<Rigidbody>() != NULL) {
			newGameObject->GetComponent<Rigidbody>()->SetKinematic(true);
			/*newGameObject->GetComponent<Renderer>()->LoadTexture(m_dxBase->GetDeviceResource(), L"Resources/scott.png");
			newGameObject->GetComponent<Animation>()->ResetAnimation(2, 8);*/
		}
		first = false;
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("D")) {
		newGameObject->GetComponent<Renderer>()->LoadTexture(m_dxBase->GetDeviceResource(), L"Resources/scott.png");
		newGameObject->GetComponent<Animation>()->ResetAnimation(2, 8);
	}
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update();
	tilemap->Update();
	//camera->SetPosition(camera->GetPosition() + Vector3(2.f, 0, 0));
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), gameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
	newGameObject->Render();
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	m_dxBase->CreateCamera(&camera);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/marioworld1-1.tmx");
	//sprite = new Sprite(m_dxBase->GetDeviceResource(), L"Resources/run.png");
	tilemap->SetCamera(camera);
	newGameObject = new GameObject();
	newGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/run.png"));
	newGameObject->GetTransform()->SetPosition(Vector3(100, 0, 0));
	newGameObject->AddComponent<Rigidbody>(new Rigidbody(newGameObject));
	newGameObject->AddComponent<Collider>(new Collider(newGameObject, newGameObject->GetTransform()));
	newGameObject->AddComponent<Animation>(new Animation(newGameObject->GetComponent<Renderer>(), 1, 10, 0.001f));
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	//gameObjectList->insert(gameObjectList->end(), sprite);
	//gameObjectList->insert(gameObjectList->end(), newGameObject);
}

void TilemapScene::UnloadScene()
{
}