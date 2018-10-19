#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Transform.h"

namespace DirectXCore
{
	class GameObject:public Object
	{
	public:
		GameObject();
		virtual void Update();
		virtual void Render();
		BoundingBox* GetBoxCollider() { return boxCollider; }
		Transform* GetTransform() { return transform; }
		virtual void OnCollisionEnter();
		~GameObject();
	protected:
		BoundingBox* boxCollider;
		Transform* transform;
	};
}

