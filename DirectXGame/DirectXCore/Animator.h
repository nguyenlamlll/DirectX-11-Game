#pragma once
#include "DxBase.h"
#include "Component.h"

namespace DirectXCore
{
	struct TransitionInfo
	{
		std::string firstAnim, secondAnim;
		bool condition;
	};

	class Animator : public Component
	{
	public:
		Animator();
		Animator(Renderer* mainRenderer);
		~Animator();
		void PreUpdate(float _deltaTime) override;
		void Update(float _deltaTime) override;
		void LateUpdate(float _deltaTime) override;
		void Render();
		bool loop;
		void AddAnimation(std::pair<std::string, Animation*>* _animation);
		void AddAnimation(Animation * _animation);
		void AddTransition(std::pair<std::string, std::string>* _transition);
		void AddTransition(std::string _firstAnim, std::string _secondAnim,bool _condition);
		void SetBool(TransitionInfo* _transitionInfo, bool _status);
		void SetBool(std::string _firstAnim, std::string _secondAnim, bool _status);
		void SetCurrentAnimation(Animation* _anim);
		Animation* GetCurrentAnimation() { return currentAnimation; }

	private:
		/*int frameIndex = 0, frameCount, frameWidth, frameHeight;
		std::vector<RECT*> animationFrameRects;
		Sprite* mainSprite;
		Renderer* mainrender;
		float currentFrameTime = 0, timePerFrame = 0, scale = 0;
		const wchar_t* name;*/
		std::vector<Animation*>* animationList;
		std::vector<TransitionInfo*>* transitionList;
		Animation* currentAnimation;
		Renderer* renderer;
	};
}

