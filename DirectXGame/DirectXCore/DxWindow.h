#pragma once
#include "DxBase.h"
namespace DirectXCore 
{
	class DxWindow : public DxBase
	{
	public:
		DxWindow();
		~DxWindow();

		bool LoadContent();
		void UnloadContent();

		void Update(float dt);
		void Render();
	};
}


