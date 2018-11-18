#pragma once

#include "stdafx.h"
#include "Sprite.h"
#include "Renderer.h"

namespace DirectXCore 
{
	class Animation : public Component
	{
	public:
		Animation();
		Animation(Sprite *_sprite, int _rows, int _collums, float _timePerFrame, float _scale = 1.0f);
		Animation(int _rows, int _collums, float _timePerFrame, float _timeScale = 1.0f);
		Animation(Renderer* mainRenderer,int _rows, int _collums, float _timePerFrame, float _timeScale = 1.0f);
		void ResetAnimation(int _rows, int _collums);
		void Update(float _deltaTime);
		void Render();
		~Animation();
	private:
		int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
	};
}


