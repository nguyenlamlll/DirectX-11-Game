#pragma once
#include "Component.h"

namespace DirectXCore {
	class State : public Component
	{
	public:
		State();
		State(GameObject* _gameObject, std::vector<std::string> _originalStateList);
		~State();
		std::string GetState() { return currentState; };
		bool FindState(std::string state);
		void SetState(std::string _state);
	private:
		std::string currentState;
		std::vector<std::string> stateList;
	};
}

