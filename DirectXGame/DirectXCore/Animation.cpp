#include "stdafx.h"
#include "Animation.h"
using namespace DirectXCore;

Animation::Animation()
{
}

Animation::Animation(int _rows, int _collums, Sprite* _sprite,float _timePerFrame, float _scale)
{
	mainSprite = _sprite;
	timePerFrame = _timePerFrame;
	scale = _scale;

	frameWidth = (mainSprite->GetSpriteRect().right - mainSprite->GetSpriteRect().left) / _collums;
	frameHeight = (mainSprite->GetSpriteRect().bottom - mainSprite->GetSpriteRect().top) / _rows;

	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _collums; j++)
		{
			RECT *rc = new RECT();
			rc->left = frameWidth * j;
			rc->top = frameHeight * i;
			rc->right = frameWidth * (j + 1);
			rc->bottom = frameHeight * (i + 1);
			animationFrameRects.emplace_back(rc);
		}
	}
	mainSprite->SetSpriteRect(animationFrameRects[0]);
	frameCount = _rows * _collums;

	DirectX::SimpleMath::Vector2* newCenter = new DirectX::SimpleMath::Vector2(frameWidth / 2, frameHeight / 2);
	mainSprite->SetCenter(*newCenter);
}

void Animation::Update(float _deltaTime)
{
	if (currentFrameTime >= timePerFrame) {
		currentFrameTime = 0;

		if (frameIndex >= frameCount-1) frameIndex = 0;
		else frameIndex += 1;
		mainSprite->SetSpriteRect(animationFrameRects[frameIndex]);
	}
	else currentFrameTime += _deltaTime;
}

void Animation::Render()
{
	mainSprite->RenderSprite();
}


Animation::~Animation()
{
	if (mainSprite) { delete mainSprite; }
}
