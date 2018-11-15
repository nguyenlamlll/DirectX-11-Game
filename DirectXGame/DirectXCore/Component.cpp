#include "stdafx.h"
#include "Component.h"

using namespace DirectXCore;

Component::Component()
{
}

DirectXCore::Component::Component(GameObject * _gameObject)
{
	attachedGameObject = _gameObject;
}

void DirectXCore::Component::SetAttachedGameObject(GameObject * _gameObject)
{
	attachedGameObject = _gameObject;
}

Component::~Component()
{
}
