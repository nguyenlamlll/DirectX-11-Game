#pragma once
#include "stdafx.h"
#include "Object.h"

namespace DirectXCore
{
	class Collision : Object
	{
	public:
		Collision(); 
		//static DirectX::ContainmentType CollisionType(DirectX::BoundingBox _thisObject, DirectX::BoundingBox _thatObject);
		~Collision();
	private:
		Object *containObject;
	};
}

