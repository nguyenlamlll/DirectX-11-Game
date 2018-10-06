#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Collision.h"

namespace DirectXCore
{
	class GameObject:public Object
	{
	public:
		GameObject();
		BoundingBox GetBoxCollider() { return boxCollider; }
		~GameObject();
	private:
		BoundingBox boxCollider;
	};
}

