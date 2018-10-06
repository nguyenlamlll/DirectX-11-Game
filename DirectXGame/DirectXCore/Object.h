#pragma once
#include "Transform.h"
using namespace DirectX;

namespace DirectXCore
{
	class Object
	{
	public:
		Object();
		Transform* GetTransform() { return transform; }

		~Object();
	protected:
		std::string tag, name;
		DirectXCore::Transform* transform;
	};
}


