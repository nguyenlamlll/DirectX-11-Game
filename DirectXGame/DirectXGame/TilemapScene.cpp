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
	newGameObject->GetComponent<Animation>()->Update(elapsedTime);
	int a = 0;
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->PreUpdate(elapsedTime);
	newGameObject->PreUpdate(elapsedTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("D")) {
		//CHANGES CURRENT STATE TO "SHOOT"
		//newGameObject->GetComponent<State>()->SetState("shoot");
		//newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/stand_attack.png", 1, 2);
		camera->SetPosition(camera->GetPosition() + Vector3(30, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A")) {
		// CHANGES CURRENT STAGE TO "RUN"
		//newGameObject->GetComponent<State>()->SetState("run");
		//newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/run.png", 1, 11);
		camera->SetPosition(camera->GetPosition() + Vector3(-30, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("W")) {
		// CHANGES CURRENT STAGE TO "RUN"
		//newGameObject->GetComponent<State>()->SetState("run");
		//newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/run.png", 1, 11);
		camera->SetPosition(camera->GetPosition() + Vector3(0, -30, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("S")) {
		// CHANGES CURRENT STAGE TO "RUN"
		//newGameObject->GetComponent<State>()->SetState("run");
		//newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/run.png", 1, 11);
		camera->SetPosition(camera->GetPosition() + Vector3(0, 30, 0));
	}

	newGameObject->GetComponent<Collider>()->SetColliderScale(Vector3(46, 46, 1));
	newGameObject->GetComponent<Collider>()->SetColliderPosition(newGameObject->GetTransform()->GetPosition());
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (newGameObject != gameObjectList->at(i) && gameObjectList->at(i)->GetComponent<Collider>())
		{
			if (newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x < gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x && newGameObject->GetTransform()->GetPosition().y < gameObjectList->at(i)->GetTransform()->GetPosition().y)
				a = 1;
			bool colType = newGameObject->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*newGameObject->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) collide = true;
		}
	}
	if (collide) {
		if (a == 1)
			int b = 2;
		newGameObject->GetComponent<Rigidbody>()->SetVelocity(Vector3(0,0,0));
		//newGameObject->GetComponent<Rigidbody>()->SetKinematic(true);
		//CHANGES CURRENT STATE TO "STAND"
		//newGameObject->GetComponent<State>()->SetState("stand");
		//newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/start2.png", 1, 6);
	}

	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update(elapsedTime);
	newGameObject->Update(elapsedTime);
	//tilemap->Update();

	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->LateUpdate(elapsedTime);
	newGameObject->LateUpdate(elapsedTime);
}

void TilemapScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetBound().right / 2 - camera->GetPosition().x, camera->GetBound().bottom / 2 - camera->GetPosition().y, 0);
	newGameObject->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
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
	GameObject *newPCN = new GameObject();
	m_dxBase->CreateCamera(&camera);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/map.tmx");
	tilemap->SetCamera(camera);
	newGameObject = new GameObject();
	newGameObject->GetTransform()->SetPosition(Vector3(100, 0, 0));
	newGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	newGameObject->AddComponent<Rigidbody>(new Rigidbody(newGameObject));
	newGameObject->AddComponent<Collider>(new Collider(newGameObject, newGameObject->GetTransform()));
	newGameObject->AddComponent<Animation>(new Animation(newGameObject->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
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
	//gameObjectList->insert(gameObjectList->end(), newPCN);
}

void TilemapScene::UnloadScene()
{
}