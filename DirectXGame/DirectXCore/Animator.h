#pragma once
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
		//SimpleMath::Vector3 GetFrameScale() { return SimpleMath::Vector3(frameWidth, frameHeight, 0); }
	private:
		/*int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
		const wchar_t* name;*/
	};
}

