#pragma once
#include "DirectXCore.h"
using namespace DirectXCore;

namespace DirectXCore
{
	class ObjectManager :public Singleton<ObjectManager>
	{
	private:
		typedef std::vector<GameObject*> ObjectList;
		ObjectList* objects;

	public:
		ObjectManager()
		{
			objects = new ObjectList();
		}
		~ObjectManager();
		void PreUpdate(float deltatime)
		{
			for (size_t i = 0; i < objects->size(); i++)
			{
				objects->at(i)->PreUpdate(deltatime);
			}
		}
		void Update(float deltatime)
		{
			for (size_t i = 0; i < objects->size(); i++)
			{
				objects->at(i)->Update(deltatime);
			}
		}
		void LateUpdate(float deltatime)
		{
			for (size_t i = 0; i < objects->size(); i++)
			{
				objects->at(i)->LateUpdate(deltatime);
			}
		}
		void RegisterObject(GameObject* gameObject)
		{
			objects->push_back(gameObject);
		}
	};
}
