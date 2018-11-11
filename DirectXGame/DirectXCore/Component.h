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
		virtual void Update() {};
		virtual void Render() {};
		void SetAttachedGameObject(GameObject* _gameObject);
		~Component();
	protected:
		GameObject* attachedGameObject;
	};
}

