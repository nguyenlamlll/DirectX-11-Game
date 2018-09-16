#include "stdafx.h"
#include "Animation.h"


Animation::Animation()
{
}

Animation::Animation(int _rows, int _collums, Sprite* _sprite,float _timePerFrame)
{
	mainSprite = _sprite;

	timePerFrame = _timePerFrame;

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
			animationFrameRects.emplace_back(*rc);
		}
	}
	mainSprite->SetSpriteRect(animationFrameRects[0]);
	frameCount = _rows * _collums;
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
}
