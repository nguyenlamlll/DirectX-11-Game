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

	protected:
		std::vector<Sound> m_sounds;
		std::vector<Sprite> m_sprites;
		std::vector<Animation> m_animations;
	};

}

