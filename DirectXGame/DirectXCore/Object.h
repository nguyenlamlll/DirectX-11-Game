#pragma once
#include "Transform.h"
using namespace DirectX;

namespace DirectXCore
{
	class Object
	{
	public:
		Object();
		~Object();
	protected:
		std::string tag, name;
	};
}


