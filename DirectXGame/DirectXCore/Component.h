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
		virtual void Update() {};
		~Component();
	protected:
		GameObject* attachedGameObject;
	};
}

