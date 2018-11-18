#include "stdafx.h"
#include "State.h"
#include "GameObject.h"

using namespace DirectXCore;

State::State()
{
}

DirectXCore::State::State(GameObject* _gameObject, std::vector<std::string> _originalStateList)
{
	attachedGameObject = _gameObject;
	//stateList = _originalStateList;
	stateList.insert(stateList.end(), _originalStateList.begin(), _originalStateList.end());
}


State::~State()
{
}

bool DirectXCore::State::FindState(std::string state)
{
	return std::find(stateList.begin(), stateList.end(), state) != stateList.end();
}

void DirectXCore::State::SetState(std::string _state)
{
	currentState = _state;
}
