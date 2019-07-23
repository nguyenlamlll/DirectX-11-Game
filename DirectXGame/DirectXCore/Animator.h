#pragma once
#include "DxBase.h"
#include "Component.h"

namespace DirectXCore
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();
		void PreUpdate(float _deltaTime) override;
		void Update(float _deltaTime) override;
		void LateUpdate(float _deltaTime) override;
		void Render();
		bool loop;
		void AddAnimation(Animation* anim);
	private:
		/*int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
		const wchar_t* name;*/
		std::vector<std::pair<std::string, Animation*>*>* animationList;
	};
}

