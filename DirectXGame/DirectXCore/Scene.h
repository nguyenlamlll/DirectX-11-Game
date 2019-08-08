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
		std::vector<DirectXCore::GameObject*>* GetDynamicGameObjectList() { return dynamicGameObjectList; }
		QuadTree* GetQuadTree() { return sceneQuadTree; }
		void DeleteObject(GameObject* _obj)
		{
			//for (size_t i = 0; i < gameObjectList->size(); i++)
			//{
			//	if (gameObjectList->at(i) == _obj)
			//	{
			//		gameObjectList->erase(std::remove(gameObjectList->begin(), gameObjectList->end(), _obj), gameObjectList->end());
			//		//delete _obj;
			//		//_obj = NULL;
			//	}
			//}
			for (size_t i = 0; i < dynamicGameObjectList->size(); i++)
			{
				if (dynamicGameObjectList->at(i) == _obj)
				{
					dynamicGameObjectList->erase(std::remove(dynamicGameObjectList->begin(), dynamicGameObjectList->end(), _obj), dynamicGameObjectList->end());
					_obj = NULL;
					delete _obj;
				}
			}
		}
	protected:
		std::vector<DirectXCore::GameObject*>* gameObjectList;
		std::vector<DirectXCore::GameObject*>* dynamicGameObjectList;
		QuadTree* sceneQuadTree;
	};
}

