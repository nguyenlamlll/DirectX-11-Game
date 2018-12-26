#pragma once
#include "Sound.h"
#include "Sprite.h"
#include "Animation.h"
#include "Input.h"
#include "GameObject.h"
#include "QuadTree.h"

namespace DirectXCore
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		virtual void UpdateScene(float elapsedTime) = 0;
		virtual void RenderScene() = 0;
		virtual void LoadScene() = 0;
		virtual void UnloadScene() = 0;

		virtual void OnKeyUp(KeyCode) = 0;
		virtual void OnKeyDown(KeyCode) = 0;

		std::vector<DirectXCore::GameObject*>* GetGameObjectList() { return gameObjectList; }
		QuadTree* GetQuadTree() { return sceneQuadTree; }
	protected:
		std::vector<DirectXCore::GameObject*>* gameObjectList;
		QuadTree* sceneQuadTree;
	};
}

