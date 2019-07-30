#include "stdafx.h"
#include "Animator.h"

using namespace DirectXCore;

Animator::Animator()
{
	animationList = new std::vector<Animation*>();
	transitionList = new std::vector<TransitionInfo*>();
	currentAnimation = NULL;
}

Animator::Animator(Renderer* mainRenderer)
{
	animationList = new std::vector<Animation*>();
	transitionList = new std::vector<TransitionInfo*>();
	renderer = mainRenderer;
	currentAnimation = NULL;
}


Animator::~Animator()
{
}

void DirectXCore::Animator::PreUpdate(float _deltaTime)
{
	if (currentAnimation != NULL) currentAnimation->PreUpdate(_deltaTime);
}

void DirectXCore::Animator::Update(float _deltaTime)
{
	if (currentAnimation != NULL)
	{
		Vector3 frameScale = currentAnimation->GetFrameScale();
		frameScale.x /= 2;
		frameScale.y /= 2;
		renderer->SetPivot(frameScale);
		renderer->SetRECT(*currentAnimation->GetCurrentRect());
		currentAnimation->Update(_deltaTime);
	}
}

void DirectXCore::Animator::LateUpdate(float _deltaTime)
{
	if (currentAnimation != NULL) currentAnimation->LateUpdate(_deltaTime);
}

void DirectXCore::Animator::Render()
{
	if (currentAnimation != NULL) currentAnimation->Render();
}

void DirectXCore::Animator::AddAnimation(std::pair<std::string, Animation*>* _animation)
{
	//animationList->push_back(_animation);
}

void DirectXCore::Animator::AddAnimation(Animation * _animation)
{
	animationList->push_back(_animation);
}

void DirectXCore::Animator::AddTransition(std::pair<std::string, std::string>* _transition)
{
	//transitionList->push_back(_transition);
}

void DirectXCore::Animator::AddTransition(std::string _firstAnim, std::string _secondAnim, bool _condition)
{
	TransitionInfo* transistionPair = new TransitionInfo();
	transistionPair->firstAnim = _firstAnim;
	transistionPair->secondAnim = _secondAnim;
	transistionPair->condition = _condition;
	transitionList->push_back(transistionPair);
}

void DirectXCore::Animator::SetBool(TransitionInfo * _transitionInfo, bool _status)
{
	for (size_t i = 0; i < transitionList->size(); i++)
	{
		if (transitionList->at(i)->firstAnim == _transitionInfo->firstAnim && transitionList->at(i)->secondAnim == _transitionInfo->secondAnim)
		{
			if (currentAnimation->GetAnimationName() == _transitionInfo->firstAnim)
			{
				for (size_t j = 0; j < animationList->size(); j++)
				{
					if (_transitionInfo->secondAnim == animationList->at(j)->GetAnimationName())
					{
						if (!currentAnimation->interupt) if (currentAnimation->lastFrame) currentAnimation = animationList->at(j);
					}
				}
			}
		}
	}
}

void DirectXCore::Animator::SetBool(std::string _firstAnim, std::string _secondAnim, bool _status)
{
	for (size_t i = 0; i < transitionList->size(); i++)
	{
		if (transitionList->at(i)->firstAnim == _firstAnim && transitionList->at(i)->secondAnim == _secondAnim && transitionList->at(i)->condition == _status)
		{
			if (currentAnimation->GetAnimationName() == _firstAnim)
			{
				for (size_t j = 0; j < animationList->size(); j++)
				{
					if (_secondAnim == animationList->at(j)->GetAnimationName())
					{
						if (!currentAnimation->interupt)
						{
							if (currentAnimation->lastFrame)
							{
								if (currentAnimation->GetAnimationName() != animationList->at(j)->GetAnimationName())
								{
									currentAnimation = animationList->at(j);
									renderer->LoadTexture(currentAnimation->GetPath());
									Vector3 frameScale = currentAnimation->GetFrameScale();
									frameScale.x /= 2;
									frameScale.y /= 2;
									renderer->SetPivot(frameScale);
									renderer->SetRECT(*currentAnimation->GetCurrentRect());
								}
							}
						}
						else
						{
							if (currentAnimation->GetAnimationName() != animationList->at(j)->GetAnimationName())
							{
								currentAnimation = animationList->at(j);
								renderer->LoadTexture(currentAnimation->GetPath());
								Vector3 frameScale = currentAnimation->GetFrameScale();
								frameScale.x /= 2;
								frameScale.y /= 2;
								renderer->SetPivot(frameScale);
								renderer->SetRECT(*currentAnimation->GetCurrentRect());
							}
						}
					}
				}
			}
		}
	}
}

void DirectXCore::Animator::SetBool(std::string _secondAnim, bool _status)
{
	if (_status)
	{
		for (size_t j = 0; j < animationList->size(); j++)
		{
			if (_secondAnim == animationList->at(j)->GetAnimationName())
			{
				if (!currentAnimation->interupt)
				{
					if (currentAnimation->lastFrame)
					{
						if (currentAnimation->GetAnimationName() != animationList->at(j)->GetAnimationName())
						{
							currentAnimation = animationList->at(j);
							renderer->LoadTexture(currentAnimation->GetPath());
							Vector3 frameScale = currentAnimation->GetFrameScale();
							frameScale.x /= 2;
							frameScale.y /= 2;
							renderer->SetPivot(frameScale);
							renderer->SetRECT(*currentAnimation->GetCurrentRect());
						}
					}
				}
				else
				{
					if (currentAnimation->GetAnimationName() != animationList->at(j)->GetAnimationName())
					{
						currentAnimation = animationList->at(j);
						renderer->LoadTexture(currentAnimation->GetPath());
						Vector3 frameScale = currentAnimation->GetFrameScale();
						frameScale.x /= 2;
						frameScale.y /= 2;
						renderer->SetPivot(frameScale);
						renderer->SetRECT(*currentAnimation->GetCurrentRect());
					}
				}
			}
		}
	}
	
}

void DirectXCore::Animator::SetCurrentAnimation(Animation * _anim)
{
	currentAnimation = _anim;
	renderer->LoadTexture(_anim->GetPath());
}
