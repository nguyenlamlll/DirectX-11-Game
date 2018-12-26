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
	sceneQuadTree->GetBranchNodesWithCamera(sceneQuadTree, camera->GetPosition(), Vector3(100, 100, 1), elapsedTime, objlist);
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->PreUpdate(elapsedTime);
	/*for (size_t i = 0; i < listMobileGameObjects->size(); i++)
	{
		if (listMobileGameObjects->at(i)->GetComponent<Collider>() && listMobileGameObjects->at(i)->GetTag()=="Player")
		{
			for (size_t j = 0; j < objlist->size(); j++)
			{
				if (objlist->at(j)->GetComponent<Collider>())
				{
					bool colType = objlist->at(j)->GetComponent<Collider>()->GetCollider()->Intersects(*listMobileGameObjects->at(i)->GetComponent<Collider>()->GetCollider());
					if (colType)
					{
						float distanceX = listMobileGameObjects->at(i)->GetTransform()->GetPosition().x - objlist->at(j)->GetTransform()->GetPosition().x;
						float distanceY = listMobileGameObjects->at(i)->GetTransform()->GetPosition().y - objlist->at(j)->GetTransform()->GetPosition().y;
						float extentDistanceX = objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.x + listMobileGameObjects->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x;
						float extentDistanceY = objlist->at(j)->GetComponent<Collider>()->GetCollider()->Extents.y + listMobileGameObjects->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;

						if (listMobileGameObjects->at(i)->GetComponent<Rigidbody>())
						{
							if (abs(distanceX) < extentDistanceX)
							{
								if (abs(distanceX) < extentDistanceX * 9 / 10)
								{
									if ((listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
										normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
									else if ((listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
										normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
								}
							}
							else;
							if (abs(distanceY) < extentDistanceY)
							{
								if (abs(distanceY) < extentDistanceY * 8.5f / 10)
								{
									if ((listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x > 0 || listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x > 0) && distanceX < 0)
										normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
									else if ((listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetAcceleration().x < 0 || listMobileGameObjects->at(i)->GetComponent<Rigidbody>()->GetMovingVector().x < 0) && distanceX > 0)
										normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
								}
							}
							else;
						}

						objlist->at(j)->GetComponent<Collider>()->SetCollisionStatus(true);
						listMobileGameObjects->at(i)->GetComponent<Collider>()->SetCollisionStatus(true);
						listMobileGameObjects->at(i)->GetComponent<Collider>()->OnCollisionEnter(objlist->at(j)->GetComponent<Collider>(), normal);
						objlist->at(j)->GetComponent<Collider>()->OnCollisionEnter(newPlayer->GetComponent<Collider>(), normal*-1);

						if (objlist->at(j)->GetTag() == "Elevator")
						{
							if (objlist->at(j)->GetTransform()->GetPosition().y > 1760)
							{
								objlist->at(j)->GetTransform()->SetPosition(objlist->at(j)->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
								newPlayer->GetTransform()->SetPosition(newPlayer->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
							}
						}
					}
				}
			}
		}
		else if (listMobileGameObjects->at(i)->GetComponent<Collider>() && listMobileGameObjects->at(i)->GetTag() == "bullet")
		{
			for (size_t j = 0; j < objlist->size(); j++)
			{
				if (objlist->at(j)->GetComponent<Collider>() && objlist->at(j)->GetTag() == "Enemy")
				{
					bool colType = objlist->at(j)->GetComponent<Collider>()->GetCollider()->Intersects(*listMobileGameObjects->at(i)->GetComponent<Collider>()->GetCollider());
					if (colType)
					{
						listMobileGameObjects->erase(listMobileGameObjects->begin() + i);
						i--;
					}
				}
			}
		}
	}*/
	/*for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		if (gameObjectList->at(i)->GetComponent<Collider>())
		{
			gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(false);
			if (gameObjectList->at(i)->GetTag() == "Wall" || gameObjectList->at(i)->GetTag() == "Elevator")
			{
				bool colType = newPlayer->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
				if (colType)
				{
					float distanceX = newPlayer->GetTransform()->GetPosition().x - gameObjectList->at(i)->GetTransform()->GetPosition().x;
					float distanceY = newPlayer->GetTransform()->GetPosition().y - gameObjectList->at(i)->GetTransform()->GetPosition().y;
					float extentDistanceX = newPlayer->GetComponent<Collider>()->GetCollider()->Extents.x + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.x;
					float extentDistanceY = newPlayer->GetComponent<Collider>()->GetCollider()->Extents.y + gameObjectList->at(i)->GetComponent<Collider>()->GetCollider()->Extents.y;

					if (abs(distanceX) < extentDistanceX)
					{
						if (abs(distanceX) < extentDistanceX * 9 / 10)
						{
							if ((newPlayer->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || newPlayer->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
								normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
							else if ((newPlayer->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || newPlayer->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
								normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
						}
					}
					else;
					if (abs(distanceY) < extentDistanceY)
					{
						if (abs(distanceY) < extentDistanceY * 8.5f / 10)
						{
							if ((newPlayer->GetComponent<Rigidbody>()->GetAcceleration().x > 0 || newPlayer->GetComponent<Rigidbody>()->GetMovingVector().x > 0) && distanceX < 0)
								normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
							else if ((newPlayer->GetComponent<Rigidbody>()->GetAcceleration().x < 0 || newPlayer->GetComponent<Rigidbody>()->GetMovingVector().x < 0) && distanceX > 0)
								normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
						}
					}
					else;

					gameObjectList->at(i)->GetComponent<Collider>()->SetCollisionStatus(true);
					newPlayer->GetComponent<Collider>()->OnCollisionEnter(gameObjectList->at(i)->GetComponent<Collider>(), normal);
					gameObjectList->at(i)->GetComponent<Collider>()->OnCollisionEnter(newPlayer->GetComponent<Collider>(), normal*-1);
					if (gameObjectList->at(i)->GetTag() == "Elevator")
					{
						if (gameObjectList->at(i)->GetTransform()->GetPosition().y > 1760)
						{
							gameObjectList->at(i)->GetTransform()->SetPosition(gameObjectList->at(i)->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
							newPlayer->GetTransform()->SetPosition(newPlayer->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
						}
					}
				}
			}
			else if (gameObjectList->at(i)->GetTag() == "Enemy")
			{
				for (size_t j = 0; j < gameObjectList->size(); j++)
				{
					if (gameObjectList->at(j)->GetComponent<Collider>())
					{
						if (gameObjectList->at(j)->GetTag() == "bullet")
						{
							bool colType = gameObjectList->at(j)->GetComponent<Collider>()->GetCollider()->Intersects(*gameObjectList->at(i)->GetComponent<Collider>()->GetCollider());
							if (colType)
							{
								gameObjectList->erase(gameObjectList->begin() + j);
							}
						}
					}
				}
			}
		}

	}*/
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
						if (objlist->at(j)->GetTag() == "Elevator")
						{
							if (objlist->at(j)->GetTransform()->GetPosition().y > 1760)
							{
								objlist->at(j)->GetTransform()->SetPosition(objlist->at(j)->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
								objlist->at(i)->GetTransform()->SetPosition(objlist->at(i)->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
							}
						}
						normal = Vector3(0, 0, 0);
					}
				}
			}
		}
	}
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->Update(elapsedTime);
	for (size_t i = 0; i < objlist->size(); i++) objlist->at(i)->LateUpdate(elapsedTime);
	camera->SetPosition(newPlayer->GetTransform()->GetPosition());
	//camera->SetPosition(Vector3(15000, 4500, 0));
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
	m_dxBase->CreateCamera(&camera);
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
	}
	gameObjectList->insert(gameObjectList->end(), tilemap->GetListGameObjects()->begin(), tilemap->GetListGameObjects()->end());
	sceneQuadTree = new QuadTree(tilemap->GetRegion(), 1, 3);
	for (size_t i = 0; i < gameObjectList->size(); i++)
	{
		sceneQuadTree->Insert(gameObjectList->at(i));
		tilemap->GetQuadTree()->Insert(gameObjectList->at(i));
	}

	camera->SetPosition(newPlayer->GetTransform()->GetPosition());
	Elevator* newElevator = new Elevator(m_dxBase);
	newElevator->SetTag("Elevator"); 
	gameObjectList->insert(gameObjectList->end(), newElevator);

	newPlayer->GetTransform()->SetPosition(Vector3(9400, 4650, 0));
	//camera->SetPosition(Vector3(31250, 7600, 0));
}

void TilemapScene::UnloadScene()
{
}