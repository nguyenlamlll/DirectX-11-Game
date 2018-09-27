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

		virtual void UpdateScene() = 0;
		virtual void LoadScene() = 0;
		virtual void UnloadScene() = 0;

	protected:
		std::vector<Sound> m_sounds;
		std::vector<Sprite> m_sprites;
		std::vector<Animation> m_animations;
		Sprite m_background;
	};

}

