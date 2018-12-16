#include "TilemapScene.h"
#include <cstdlib>

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
	Vector3 normal = Vector3(0, 0, 0);
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->PreUpdate(elapsedTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
	{
		//newGameObject->GetComponent<Rigidbody>()->Move(Vector3(100, 0, 0));
		newGameObject->GetComponent<Rigidbody>()->AddForce(Vector3(3, 0, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(10, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		//newGameObject->GetComponent<Rigidbody>()->Move(Vector3(-100, 0, 0));
		newGameObject->GetComponent<Rigidbody>()->AddForce(Vector3(-3, 0, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(-10, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("W"))
	{
		// CHANGES CURRENT STAGE TO "RUN"
		//newGameObject->GetComponent<Rigidbody>()->SetVelocity(newGameObject->GetComponent<Rigidbody>()->GetVelocity() + Vector3(0, -40, 0));
		newGameObject->GetComponent<Rigidbody>()->AddForce(Vector3(0, -50, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(0, -10, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("S"))
	{
		//camera->SetPosition(camera->GetPosition() + Vector3(0, 10, 0));
	}

	newGameObject->GetComponent<Collider>()->SetCollisionStatus(false);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (newGameObject != gameObjectList->at(i) && gameObjectList->at(i)->GetComponent<Collider>())
		{
			gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
			bool colType = newGameObject->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
			if (colType) {
				//if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().y > 0)
				//{
				//	float distance = abs(newGameObject->GetTransform()->GetPosition().x - gameObjectList->at(i)->GetTransform()->GetPosition().x) ;
				//	float extentDistance = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x;
				//	//float distanceX = abs(newGameObject->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y);
				//	//float extentDistanceX = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;
				//	if (distance <= extentDistance-20) normal += Vector3(0, -1, 0);
				//}
				//else if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().y < 0)
				//{
				//	float distance = abs(newGameObject->GetTransform()->GetPosition().x - gameObjectList->at(i)->GetTransform()->GetPosition().x);
				//	float extentDistance = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x;
				//	//float distanceX = abs(newGameObject->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y);
				//	//float extentDistanceX = gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;
				//	if (distance <= extentDistance-20) normal += Vector3(0, 1, 0);
				//}
				//if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().x > 0)
				//{
				//	float distance = abs(newGameObject->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y);
				//	float extentDistance = newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;
				//	if (distance < extentDistance-20) normal += Vector3(-1, 0, 0);
				//}
				//else if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().x > 0)
				//{
				//	float distance = abs(newGameObject->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y);
				//	float extentDistance = newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;
				//	if (distance < extentDistance - 20) normal += Vector3(-1, 0, 0);
				//}
				/*if (newGameObject->GetTransform()->GetPosition().y < gameObjectList->at(i)->GetTransform()->GetPosition().y)
				{
					if (normal.y == 0 && newGameObject->GetComponent<Rigidbody>()->GetVelocity().y > 0) {
						if (newGameObject->GetTransform()->GetPosition().x + newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x < gameObjectList->at(i)->GetTransform()->GetPosition().x + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x
							|| newGameObject->GetTransform()->GetPosition().x - newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x > gameObjectList->at(i)->GetTransform()->GetPosition().x - gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x)
							normal += Vector3(0, -1, 0);
					}
					else;
				}
				else if (newGameObject->GetTransform()->GetPosition().y > gameObjectList->at(i)->GetTransform()->GetPosition().y)
				{
					if (normal.y == 0 && newGameObject->GetComponent<Rigidbody>()->GetVelocity().y < 0 && newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x < gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x) normal += Vector3(0, 1, 0);
					else;
				}
				if (newGameObject->GetTransform()->GetPosition().x < gameObjectList->at(i)->GetTransform()->GetPosition().x)
				{
					if (normal.x == 0 && newGameObject->GetComponent<Rigidbody>()->GetVelocity().x > 0)
					{
						if (newGameObject->GetTransform()->GetPosition().y + newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y < gameObjectList->at(i)->GetTransform()->GetPosition().y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y);
						else normal += Vector3(-1, 0, 0);
					}
					else;
				}
				else if (newGameObject->GetTransform()->GetPosition().x > gameObjectList->at(i)->GetTransform()->GetPosition().x)
				{
					if (normal.x == 0 && newGameObject->GetComponent<Rigidbody>()->GetVelocity().x < 0 && newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y < gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y) normal += Vector3(1, 0, 0);
					else;
				}*/
				float distanceX = newGameObject->GetTransform()->GetPosition().x - gameObjectList->at(i)->GetTransform()->GetPosition().x;
				float distanceY = newGameObject->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y;
				float extentDistanceX = newGameObject->GetComponent<Collider>()->GetCollider()->Extents.x + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x;
				float extentDistanceY = newGameObject->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;

				if (abs(distanceX) < extentDistanceX)
				{
					if (abs(distanceX) < extentDistanceX * 9 / 10)
					{
						if (newGameObject->GetComponent<Rigidbody>()->GetAcceleration().y > 0 && distanceY < 0)
							normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
						else if (newGameObject->GetComponent<Rigidbody>()->GetAcceleration().y < 0 && distanceY > 0)
							normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
					}
				}
				else;
				if (abs(distanceY) < extentDistanceY)
				{
					if (abs(distanceY) < extentDistanceY * 8.5f / 10)
					{
						if (newGameObject->GetComponent<Rigidbody>()->GetAcceleration().x > 0 && distanceX < 0)
							normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
						else if (newGameObject->GetComponent<Rigidbody>()->GetAcceleration().x < 0 && distanceX > 0)
							normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
					}
				}
				else;
				gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(true);
				newGameObject->GetComponent<Collider>()->SetCollisionStatus(true);
				Vector3 objectVec = newGameObject->GetComponent<Rigidbody>()->GetAcceleration();
				objectVec.x = (normal.x > 0) ? -objectVec.x : objectVec.x;
				objectVec.y = (normal.y > 0) ? -objectVec.y : objectVec.y;
				Vector3 newVec = objectVec * normal + newGameObject->GetComponent<Rigidbody>()->GetVelocity();
				//newGameObject->GetComponent<Rigidbody>()->SetVelocity(newVec);
				newGameObject->GetComponent<Rigidbody>()->AddForce(objectVec*normal);
			}
		}
	}
	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->Update(elapsedTime);
	/*if (newGameObject->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (normal.x != 0 && normal.y == 0)
		{
			if (newGameObject->GetComponent<State>())
			{
				if (newGameObject->GetComponent<State>()->GetState() != "sweep")
				{
					newGameObject->GetComponent<State>()->SetState("sweep");
					newGameObject->GetComponent<Animation>()->ResetAnimation((normal.x < 0) ? L"Resources/Animations/sweep_wall.png" : L"Resources/Animations/sweep_wall_flip.png", 1, 3);
				}
			}
		}
		else if (normal.y != 0 && normal.x == 0)
		{
			if (m_dxBase->GetInputManager()->IsKeyDown("A") || m_dxBase->GetInputManager()->IsKeyDown("D"))
			{
				if (newGameObject->GetComponent<State>())
				{
					if (newGameObject->GetComponent<State>()->GetState() != "run") {
						newGameObject->GetComponent<State>()->SetState("run");
						newGameObject->GetComponent<Animation>()->ResetAnimation((newGameObject->GetComponent<Rigidbody>()->GetVelocity().x > 0) ? L"Resources/Animations/run.png" : L"Resources/Animations/run_flip.png", 1, 11);
					}
				}
			}
			else
			{
				if (newGameObject->GetComponent<State>())
				{
					if (newGameObject->GetComponent<State>()->GetState() != "stand") {
						newGameObject->GetComponent<State>()->SetState("stand");
						newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/stand.png", 1, 4);
					}
				}
			}
		}
	}
	else
	{
		if (newGameObject->GetComponent<State>())
		{
			if (newGameObject->GetComponent<State>()->GetState() != "jump")
			{
				newGameObject->GetComponent<State>()->SetState("jump");
				newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/jump.png", 1, 7);
			}
		}
	}*/
	if (newGameObject->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (newGameObject->GetComponent<Rigidbody>()->GetVelocity().x != 0)
		{
			if (newGameObject->GetComponent<State>())
			{
				if (newGameObject->GetComponent<State>()->GetState() != "run") {
					newGameObject->GetComponent<State>()->SetState("run");
					newGameObject->GetComponent<Animation>()->ResetAnimation((newGameObject->GetComponent<Rigidbody>()->GetVelocity().x > 0) ? L"Resources/Animations/run.png" : L"Resources/Animations/run_flip.png", 1, 11);
				}
			}
		}
	}
	else
	{
		if (newGameObject->GetComponent<State>())
		{
			if (newGameObject->GetComponent<State>()->GetState() != "jump")
			{
				newGameObject->GetComponent<State>()->SetState("jump");
				newGameObject->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/jump.png", 1, 7);
			}
		}
	}
	//tilemap->GetQuadTree()->UpdateWithCamera(camera->GetPosition(), Vector3(500, 500, 1), elapsedTime);

	for (size_t i = 0; i < gameObjectList->size(); i++) gameObjectList->at(i)->LateUpdate(elapsedTime);

	camera->SetPosition(newGameObject->GetTransform()->GetPosition());
}

void TilemapScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
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
	//newGameObject->Render();
}

void TilemapScene::LoadScene()
{
	gameObjectList = new std::vector<GameObject*>();
	GameObject *newPCN = new GameObject();
	m_dxBase->CreateCamera(&camera);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/BlastHornetMap.tmx");
	tilemap->SetCamera(camera);
	newGameObject = new GameObject();
	newGameObject->GetTransform()->SetPosition(Vector3(50, 3500, 0));
	newGameObject->GetTransform()->SetScale(Vector3(120, 120, 1));
	newGameObject->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	newGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	newGameObject->AddComponent<Rigidbody>(new Rigidbody(newGameObject));
	newGameObject->AddComponent<Collider>(new Collider(newGameObject, newGameObject->GetTransform()));
	newGameObject->AddComponent<Animation>(new Animation(newGameObject->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("jump");
	stringStates->push_back("run");
	stringStates->push_back("runflip");
	stringStates->push_back("shoot");
	stringStates->push_back("ground");
	stringStates->push_back("stand");
	stringStates->push_back("sweep");
	stringStates->push_back("sweepflip");
	newGameObject->AddComponent<State>(new State(newGameObject, *stringStates));

	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());

	//tilemap->SetTilemapPosition(Vector3(0, 774, 0));

	m_dxBase->CreateSoundAndMusic(L"Resources/Music/09 Blast Hornet.wav", &m_backgroundMusic);
	m_backgroundMusic->Play();
	gameObjectList->insert(gameObjectList->end(), newGameObject);
}

void TilemapScene::UnloadScene()
{
}