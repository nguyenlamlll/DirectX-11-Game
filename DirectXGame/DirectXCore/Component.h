#pragma once
#include "stdafx.h"

namespace DirectXCore
{
	class Component
	{
	public:
		Component();
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		~Component();
	};
}

