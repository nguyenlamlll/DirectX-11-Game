#pragma once
#include "stdafx.h"
#include "Object.h"

namespace DirectXCore
{
	class GameObject;
	class Component :public Object
	{
	public:
		Component();
		Component(GameObject* _gameObject);
		virtual void PreUpdate(float _deltaTime) {};
		virtual void Update(float _deltaTime) {};
		virtual void LateUpdate(float _deltaTime) {};
		virtual void Render() {};
		void SetAttachedGameObject(GameObject* _gameObject);
		GameObject* GetAttachedGameObject() { return attachedGameObject; }
		~Component();
	protected:
		GameObject* attachedGameObject;
	};
}

