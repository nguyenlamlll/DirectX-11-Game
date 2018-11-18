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
	Rigidbody *rigidBody = newGameObject->GetComponent<Rigidbody>();
	if (rigidBody) {
		if (!rigidBody->IsKinematic()) rigidBody->Move(SimpleMath::Vector3(0, 9.8f*rigidBody->GetMass().y, 0), 0.5f);
		else rigidBody->Move(SimpleMath::Vector3(0, 0.f*rigidBody->GetMass().y, 0), 0.5f);
	}
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
			//CHANGES CURRENT STATE TO "STAND"
			//newGameObject->GetComponent<State>()->SetState("stand");
			newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/start2.png", 1, 6);
		}
		first = false;
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("D")) {
		//CHANGES CURRENT STATE TO "SHOOT"
		//newGameObject->GetComponent<State>()->SetState("shoot");
		newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/stand_attack.png", 1, 2);
	}
	else if (m_dxBase->GetInputManager()->IsKeyDown("A")) {
		// CHANGES CURRENT STAGE TO "RUN"
		//newGameObject->GetComponent<State>()->SetState("run");
		newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/run.png", 1, 11);
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
	tilemap->SetCamera(camera);
	newGameObject = new GameObject();
	newGameObject->GetTransform()->SetPosition(Vector3(100, 0, 0));
	newGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/run.png"));
	newGameObject->AddComponent<Rigidbody>(new Rigidbody(newGameObject));
	newGameObject->AddComponent<Collider>(new Collider(newGameObject, newGameObject->GetTransform()));
	newGameObject->AddComponent<Animation>(new Animation(newGameObject->GetComponent<Renderer>(), 1, 11, 1.0f, 1.0f, true));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	// ADDING STATES TO GAMEOBJECT ( IN BETA )
	stringStates->push_back("jump");
	stringStates->push_back("run");
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	newGameObject->AddComponent<State>(new State(newGameObject, *stringStates));


	//newGameObject->GetComponent<State>()->SetState("jump");
	newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/jump.png", 1, 7);

	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	//gameObjectList->insert(gameObjectList->end(), newGameObject);
}

void TilemapScene::UnloadScene()
{
}