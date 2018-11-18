#pragma once

#include "stdafx.h"
#include "Sprite.h"

namespace DirectXCore 
{
	class Animation : public Component
	{
	public:
		Animation();
		Animation(Sprite *_sprite, int _rows, int _collums, float _timePerFrame, float _scale = 1.0f);
		void Update(float _deltaTime);
		void Render();
		~Animation();
	private:
		int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
	};
}


