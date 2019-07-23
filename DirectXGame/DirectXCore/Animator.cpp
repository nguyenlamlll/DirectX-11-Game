#include "stdafx.h"
#include "Animator.h"

using namespace DirectXCore;

Animator::Animator()
{
	animationList = new std::vector<std::pair<std::string, Animation*>*>();
}


Animator::~Animator()
{
}

void DirectXCore::Animator::PreUpdate(float _deltaTime)
{
}

void DirectXCore::Animator::Update(float _deltaTime)
{
}

void DirectXCore::Animator::LateUpdate(float _deltaTime)
{
}

void DirectXCore::Animator::Render()
{
}
