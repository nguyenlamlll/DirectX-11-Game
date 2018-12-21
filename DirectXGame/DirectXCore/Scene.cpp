#include "stdafx.h"
#include "Scene.h"

using namespace DirectXCore;

Scene::Scene()
{
}


Scene::~Scene()
{
}

void DirectXCore::Scene::InsertGameObject(GameObject * _gameObject)
{
	if (gameObjectList != NULL) gameObjectList->insert(gameObjectList->end(), _gameObject);
	if (sceneQuadTree != NULL)sceneQuadTree->Insert(_gameObject);
}
