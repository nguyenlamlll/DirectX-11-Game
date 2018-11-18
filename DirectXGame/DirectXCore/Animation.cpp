#include "stdafx.h"
#include "Animation.h"
using namespace DirectXCore;

Animation::Animation()
{
}

Animation::Animation(Sprite* _sprite, int _rows, int _collums, float _timePerFrame, float _scale)
{
	//attachedGameObject = _sprite;
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

	//DirectX::SimpleMath::Vector3* newCenter = new DirectX::SimpleMath::Vector3(frameWidth / 2, frameHeight / 2, 0);
	//mainSprite->SetCenter(*newCenter);
	mainSprite->SetCenter(Vector3(0, 0, 0));
	//mainSprite->GetTransform()->SetScale(Vector3(frameWidth, frameHeight, 1));
}

DirectXCore::Animation::Animation(int _rows, int _collums, float _timePerFrame, float _timeScale)
{
}

DirectXCore::Animation::Animation(Renderer * mainRenderer, int _rows, int _collums, float _timePerFrame, float _timeScale)
{
	mainrender = mainRenderer;
	frameWidth = (mainrender->GetRECT()->right - mainrender->GetRECT()->left) / _collums;
	frameHeight = (mainrender->GetRECT()->bottom - mainrender->GetRECT()->top) / _rows;

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
	mainrender->SetRECT(*animationFrameRects[0]);
	frameCount = _rows * _collums;
}

void Animation::ResetAnimation(int _rows, int _collums) {
	animationFrameRects.clear();
	frameWidth = (mainrender->GetRECT()->right - mainrender->GetRECT()->left) / _collums;
	frameHeight = (mainrender->GetRECT()->bottom - mainrender->GetRECT()->top) / _rows;

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
	mainrender->SetRECT(*animationFrameRects[0]);
	frameCount = _rows * _collums;
}

void Animation::Update(float _deltaTime)
{
	if (currentFrameTime >= timePerFrame) {
		currentFrameTime = 0;

		if (frameIndex >= frameCount - 1) frameIndex = 0;
		else frameIndex += 1;
		mainrender->SetRECT(*animationFrameRects[frameIndex]);
	}
	else currentFrameTime += _deltaTime;
}

void Animation::Render()
{
	//mainSprite->Render();
}


Animation::~Animation()
{
	if (mainSprite) { delete mainSprite; }
}
