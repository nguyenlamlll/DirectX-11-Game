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
		Animation(Renderer* mainRenderer, int _rows, int _collums, float _timePerFrame, float _timeScale, bool _loop);
		void ResetAnimation(const wchar_t * _charPath,int _rows, int _collums);
		void PreUpdate(float _deltaTime) override;
		void Update(float _deltaTime) override;
		void LateUpdate(float _deltaTime) override;
		void Render();
		~Animation();
		bool loop;
		SimpleMath::Vector3 GetFrameScale() { return SimpleMath::Vector3(frameWidth, frameHeight, 0); }
	private:
		int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
		const wchar_t* name;
	};
}


