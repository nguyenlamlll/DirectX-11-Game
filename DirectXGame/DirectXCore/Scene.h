#pragma once
#include "Sound.h"
#include "Sprite.h"
#include "Animation.h"

namespace DirectXCore 
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		virtual void UpdateScene(float elapsedTime) = 0;
		virtual void RenderScene() = 0;
		virtual void LoadScene() = 0;
		virtual void UnloadScene() = 0;

	};

}

