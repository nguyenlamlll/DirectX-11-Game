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
	sceneQuadTree->ClearTree();
	for (size_t i = 0; i < gameObjectList->size(); i++) sceneQuadTree->Insert(gameObjectList->at(i));
	//if (m_dxBase->GetInputManager()->IsKeyDown("W"))camera->SetPosition(camera->GetPosition() + Vector3(0, -50, 0));
	//if (m_dxBase->GetInputManager()->IsKeyDown("A"))camera->SetPosition(camera->GetPosition() + Vector3(-50, 0, 0));
	//if (m_dxBase->GetInputManager()->IsKeyDown("S"))camera->SetPosition(camera->GetPosition() + Vector3(0, 50, 0));
	//if (m_dxBase->GetInputManager()->IsKeyDown("D"))camera->SetPosition(camera->GetPosition() + Vector3(50, 0, 0));
	std::vector<DirectXCore::GameObject*>* objlist = new  std::vector<DirectXCore::GameObject*>();
	sceneQuadTree->GetBranchNodesWithCamera(camera->GetPosition(), Vector3(1, 1, 1), elapsedTime, objlist);
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->PreUpdate(elapsedTime);
	for (size_t i = 0; i < objlist->size(); i++)
	{
		if (objlist->at(i)->GetComponent<Collider>())
		{
			objlist->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
			for (int j = 0; j < objlist->size(); j++)
			{
				if (objlist->at(j)->GetComponent<Collider>() && objlist->at(j) != objlist->at(i))
				{
					bool colType = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*objlist->at(j)->GetComponent<Collider>()->GetCollider());
					if (colType)
					{
						Vector3 normal = Vector3(0, 0, 0);
						if (i == 1)
							bool l = false;
						if (objlist->at(i)->GetComponent<Rigidbody>())
						{
							float distanceX = objlist->at(i)->GetTransform()->GetPosition().x - objlist->at(j)->GetTransform()->GetPosition().x;
							float distanceY = objlist->at(i)->GetTransform()->GetPosition().y - objlist->at(j)->GetTransform()->GetPosition().y;
							float extentDistanceX = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x + objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.x;
							float extentDistanceY = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y + objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.y;

							if (abs(distanceX) < extentDistanceX)
							{
								if (abs(distanceX) < extentDistanceX * 9 / 10)
								{
									if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
										normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
									else if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
										normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
								}
							}
							else;
							if (abs(distanceY) < extentDistanceY)
							{
								if (abs(distanceY) < extentDistanceY * 8.5f / 10)
								{
									if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x > 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x > 0) && distanceX < 0)
										normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
									else if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x < 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x < 0) && distanceX > 0)
										normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
								}
							}
							else;
						}
						objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), normal);
						objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), normal*-1);
						normal = Vector3(0, 0, 0);
					}
				}
			}
		}
	}
	for (size_t i = 0; i < objlist->size(); i++)
	{
		if (objlist->at(i)->GetComponent<Collider>())
		{
			objlist->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
			for (int j = 0; j < objlist->size(); j++)
			{
				if (objlist->at(i)->GetComponent<Collider>())
				{

				}
				float normalX, normalY;
				float contactTime = PhysicsManager::GetInstance()->CheckSweptAABB(objlist->at(i), objlist->at(j), normalX, normalY);

				if (normalY < 0 && contactTime < 1)
				{
					Vector3* normalVector = new Vector3(normalX, normalY,0);
					objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), *normalVector);
					objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), *normalVector*-1);
				}
				if (objlist->at(j)->GetComponent<Collider>() && objlist->at(j) != objlist->at(i))
				{
					bool colType = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Intersects(*objlist->at(j)->GetComponent<Collider>()->GetCollider());
					if (colType)
					{
						Vector3 normal = Vector3(0, 0, 0);
						if (i == 1)
							bool l = false;
						if (objlist->at(i)->GetComponent<Rigidbody>())
						{
							float distanceX = objlist->at(i)->GetTransform()->GetPosition().x - objlist->at(j)->GetTransform()->GetPosition().x;
							float distanceY = objlist->at(i)->GetTransform()->GetPosition().y - objlist->at(j)->GetTransform()->GetPosition().y;
							float extentDistanceX = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x + objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.x;
							float extentDistanceY = objlist->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y + objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.y;

							if (abs(distanceX) < extentDistanceX)
							{
								if (abs(distanceX) < extentDistanceX * 9 / 10)
								{
									if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
										normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
									else if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
										normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
								}
							}
							else;
							if (abs(distanceY) < extentDistanceY)
							{
								if (abs(distanceY) < extentDistanceY * 8.5f / 10)
								{
									if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x > 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x > 0) && distanceX < 0)
										normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
									else if ((objlist->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x < 0 || objlist->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x < 0) && distanceX > 0)
										normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
								}
							}
							else;
						}
						objlist->at(i)->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), normal);
						objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(i)->GetComponent<Collider>(), normal*-1);
						normal = Vector3(0, 0, 0);
					}
				}
			}
		}
	}
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->Update(elapsedTime);
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->LateUpdate(elapsedTime);

	BoundingBox * camBB = new BoundingBox(newPlayer->GetTransform()->GetPosition(), Vector3(camera->GetWidth() / 2, camera->GetHeight() / 2, 0));
	bool containsX = false;
	bool containsY = false;
	for (size_t i = 0; i < tilemap->GetListAreas()->size(); i++)
	{
		if (i == 0)
			int a = 1;
		BoundingBox * objBB = tilemap->GetListAreas()->at(i)->GetComponent<Collider>()->GetCollider();
		float distanceX = abs(camBB->Center.x - objBB->Center.x);
		float distanceY = abs(camBB->Center.y - objBB->Center.y);
		float diameterX = (objBB->Extents.x - camBB->Extents.x);
		float diameterY = objBB->Extents.y - camBB->Extents.y;
		if (distanceX <= diameterX)
			containsX = true;
		if (distanceY <= diameterY)
			containsY = true;
	}
	if (containsX || containsY) camera->SetPosition(Vector3(camBB->Center.x, camBB->Center.y, 0));
	//camera->SetPosition(Vector3(containsX ? camBB->Center.x : camera->GetPosition().x, containsY ? camBB->Center.y : camera->GetPosition().y, 0));
	delete objlist;
}

void TilemapScene::RenderScene()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	tilemap->Render();
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		gameObjectList->at(i)->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
		if (camera->IsContain(gameObjectList->at(i)->GetTransform()->GetWorldToScreenPosition(), gameObjectList->at(i)->GetTransform()->GetScreenScale()))
		{
			gameObjectList->at(i)->Render();
		}
	}
}

void TilemapScene::LoadScene()
{
	camera = new Camera(m_dxBase->GetDeviceResource()->GetOutputSize().right / 2, m_dxBase->GetDeviceResource()->GetOutputSize().bottom / 2);
	tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/BlastHornetMap.tmx");
	tilemap->SetCamera(camera);
	gameObjectList = new std::vector<GameObject*>();

	m_dxBase->CreateSoundAndMusic(L"Resources/Music/09 Blast Hornet.wav", &m_backgroundMusic);
	m_backgroundMusic->Play();

	newPlayer = new Player(m_dxBase);
	newPlayer->SetTag("Player");
	gameObjectList->insert(gameObjectList->end(), newPlayer);

	for (size_t i = 0; i < tilemap->GetListGameObjects()->size(); i++)
	{
		if (tilemap->GetListGameObjects()->at(i)->GetTag() == "Enemy")
		{
			Enemy* newEnemy = new Enemy(m_dxBase, tilemap->GetListGameObjects()->at(i)->GetTransform()->GetPosition());
			newEnemy->GetTransform()->SetScreenScale(Vector3(2, 2, 0));
			newEnemy->SetTag("Enemy");
			newEnemy->SetName(tilemap->GetListGameObjects()->at(i)->GetName());
			tilemap->GetListGameObjects()->at(i) = newEnemy;
		}
		else if (tilemap->GetListGameObjects()->at(i)->GetTag() == "Shuriken")
		{
			ShurikenBoss* newShuikenBoss = new ShurikenBoss(m_dxBase, tilemap->GetListGameObjects()->at(i)->GetTransform()->GetPosition(), Vector3(0, 0, 0), Vector3(3.5f, 3.5f, 1));
			//tilemap->GetListGameObjects()->erase(tilemap->GetListGameObjects()->begin() + i);
			//i--;
			//gameObjectList->insert(gameObjectList->end(), newShuikenBoss);
			tilemap->GetListGameObjects()->at(i) = newShuikenBoss;
		}
		else if (tilemap->GetListGameObjects()->at(i)->GetTag() == "Hornet")
		{
			HornetBoss* newHornetBoss = new HornetBoss(m_dxBase, tilemap->GetListGameObjects()->at(i)->GetTransform()->GetPosition(), Vector3(0, 0, 0), Vector3(3, 3, 3));
			tilemap->GetListGameObjects()->at(i) = newHornetBoss;
		}
	}
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	sceneQuadTree = new QuadTree(tilemap->GetRegion(), 1, 4);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		sceneQuadTree->Insert(gameObjectList->at(i));
		tilemap->GetQuadTree()->Insert(gameObjectList->at(i));
	}

	camera->SetPosition(newPlayer->GetTransform()->GetPosition());
	Elevator* newElevator = new Elevator(m_dxBase);
	newElevator->SetTag("Elevator");
	gameObjectList->insert(gameObjectList->end(), newElevator);

	//newPlayer->GetTransform()->SetPosition(Vector3(530, 3700, 0));
	//camera->SetPosition(Vector3(530, 3520, 0));
	newPlayer->GetTransform()->SetPosition(Vector3(9460, 4740, 0));
	//newPlayer->GetTransform()->SetPosition(Vector3(31220, 7600, 0));
	//camera->SetPosition(Vector3(31200, 7560, 0));
}

void TilemapScene::UnloadScene()
{
}