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
bool firstTime = false;
void TilemapScene::UpdateScene(float elapsedTime)
{
	int a = 0;
	Vector3 normal = Vector3();
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->PreUpdate(elapsedTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
	{
		// CHANGES CURRENT STAGE TO "RUN"
		if (newGameObject->GetComponent<State>()->GetState() != "run") {
			newGameObject->GetComponent<State>()->SetState("run");
			newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/run.png", 1, 11);
		}
		camera->SetPosition(camera->GetPosition() + Vector3(30, 0, 0));
		newGameObject->GetTransform()->SetPosition(newGameObject->GetTransform()->GetPosition() + Vector3(15, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		// CHANGES CURRENT STAGE TO "RUN"
		newGameObject->GetComponent<State>()->SetState("run");
		newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/run.png", 1, 11);
		camera->SetPosition(camera->GetPosition() + Vector3(-30, 0, 0));
		newGameObject->GetTransform()->SetPosition(newGameObject->GetTransform()->GetPosition() + Vector3(-15, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("W"))
	{
		// CHANGES CURRENT STAGE TO "RUN"
		newGameObject->GetComponent<State>()->SetState("run");
		newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/run.png", 1, 11);
		camera->SetPosition(camera->GetPosition() + Vector3(0, -30, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("S"))
	{
		camera->SetPosition(camera->GetPosition() + Vector3(0, 30, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("J"))
	{
		//CHANGES CURRENT STATE TO "SHOOT"
		newGameObject->GetComponent<State>()->SetState("shoot");
		newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/stand_attack.png", 1, 2);
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("K"))
	{
		newGameObject->GetComponent<Rigidbody>()->AddForce(Vector3(0, -2, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("L"))
	{
		newGameObject->GetComponent<Rigidbody>()->AddForce(Vector3(-0.5f, 0, 0));
	}
	collide = false;
	if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().x < -10)
		int p = 1;
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (newGameObject != gameObjectList->at(i) && gameObjectList->at(i)->GetComponent<Collider>())
		{
			bool colType = newGameObject->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			bool colType2 = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*newGameObject->GetComponent<Collider>()->GetCollider());
			if (colType || colType2) {
				Collider* asdasd = gameObjectList->at(i)->GetComponent<Collider>();
				if (newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x < gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x) {
					if (newGameObject->GetTransform()->GetPosition().y < gameObjectList->at(i)->GetTransform()->GetPosition().y)
					{
						if (normal.y == 0) normal += Vector3(0, -1, 0);
						else;
					}
					else
					{
						if (normal.y == 0) normal += Vector3(0, 1, 0);
						else;
					}
				}
				if (newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y < gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y)
				{
					if (newGameObject->GetTransform()->GetPosition().x < gameObjectList->at(i)->GetTransform()->GetPosition().x)
					{
						if (normal.x == 0)normal += Vector3(-1, 0, 0);
						else;
					}
					else
					{
						if (normal.x == 0)normal += Vector3(1, 0, 0);
						else;
					}
				}
				collide = true;
			}
		}
	}
	if (collide) {
		Vector3 newVec = newGameObject->GetComponent<Rigidbody>()->GetVelocity()*normal;
		newGameObject->GetComponent<Rigidbody>()->AddForce(newVec);
		if (firstTime == false)
		{
			//CHANGES CURRENT STATE TO "STAND"
			newGameObject->GetComponent<State>()->SetState("stand");
			newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/stand2.png", 1, 4);
			firstTime = true;
		}
	}

	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update(elapsedTime);
	newGameObject->Update(elapsedTime);
	//tilemap->Update();

	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->LateUpdate(elapsedTime);
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
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/BlastHornetMap.tmx");
	tilemap->SetCamera(camera);
	newGameObject = new GameObject();
	newGameObject->GetTransform()->SetPosition(Vector3(100, 0, 0));
	newGameObject->GetTransform()->SetScale(Vector3(32, 32, 1));
	newGameObject->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	newGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	newGameObject->AddComponent<Rigidbody>(new Rigidbody(newGameObject));
	newGameObject->AddComponent<Collider>(new Collider(newGameObject, newGameObject->GetTransform()));
	newGameObject->AddComponent<Animation>(new Animation(newGameObject->GetComponent<Renderer>(), 1, 11, 0.25f, 1.0f, true));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	// ADDING STATES TO GAMEOBJECT ( IN BETA )
	stringStates->push_back("jump");
	stringStates->push_back("run");
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	newGameObject->AddComponent<State>(new State(newGameObject, *stringStates));


	newGameObject->GetComponent<State>()->SetState("jump");
	newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/jump.png", 1, 7);

	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());

	m_dxBase->CreateSoundAndMusic(L"Resources/Music/09 Blast Hornet.wav", &m_backgroundMusic);
	m_backgroundMusic->Play();
	gameObjectList->insert(gameObjectList->end(), newGameObject);
	//gameObjectList->insert(gameObjectList->end(), newPCN);
}

void TilemapScene::UnloadScene()
{
}