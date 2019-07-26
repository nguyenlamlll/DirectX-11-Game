#include "stdafx.h"
#include "Scene.h"

using namespace DirectXCore;

Scene::Scene()
{
	gameObjectList = new std::vector<DirectXCore::GameObject*>();
	dynamicGameObjectList = new std::vector<DirectXCore::GameObject*>();
}


Scene::~Scene()
{
}

