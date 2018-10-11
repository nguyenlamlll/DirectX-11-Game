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
		void Update();
		BoundingBox* GetBoxCollider() { return boxCollider; }
		Transform* GetTransform() { return transform; }
		virtual void OnCollisionEnter();
		~GameObject();
	private:
		BoundingBox* boxCollider;
	protected:
		Transform* transform;
	};
}

