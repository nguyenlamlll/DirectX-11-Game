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
		Animation(std::string _name, Renderer* mainRenderer, int _rows, int _collums, float _timePerFrame, float _timeScale, bool _loop);
		Animation(const wchar_t * _charPath, std::string _name, Renderer* mainRenderer, int _rows, int _collums, float _timePerFrame, float _timeScale, bool _loop);
		void ResetAnimation(const wchar_t * _charPath, int _rows, int _collums);
		std::string GetAnimationName() { return animationName; }
		void SetAnimationName(std::string _newName) { animationName = _newName; }
		void PreUpdate(float _deltaTime) override;
		void Update(float _deltaTime) override;
		void LateUpdate(float _deltaTime) override;
		void Render();
		~Animation();
		bool loop;
		bool interupt;
		bool lastFrame = false;
		SimpleMath::Vector3 GetFrameScale() { return SimpleMath::Vector3(frameWidth, frameHeight, 0); }
		RECT* GetCurrentRect() { return currentRect; }
		const wchar_t* GetPath() { return path; }
	private:
		int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
		const wchar_t* path;
		std::string animationName;
		RECT* currentRect;
	};
}


