#pragma once

#include "stdafx.h"
#include "Sprite.h"

namespace DirectXCore 
{
	class Animation
	{
	public:
		Animation();
		Animation(int _rows, int _collums, Sprite* _sprite, float _timePerFrame);
		void Update(float _deltaTime);
		void Render();
		~Animation();
	private:
		int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT> animationFrameRects;
		Sprite* mainSprite;
		float currentFrameTime = 0;
		float timePerFrame = 0;
	};
}


