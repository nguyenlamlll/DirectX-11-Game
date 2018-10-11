#include "stdafx.h"
#include "Transform.h"

using namespace DirectXCore;

Transform::Transform()
{
}

Transform::Transform(Vector2 _pos = Vector2(0,0), Vector2 _rot = Vector2(0,0), Vector2 _scl = Vector2(1,1))
{
	position = _pos;
	rotation = _rot;
	scale = _scl;
}

void Transform::SetPosition(Vector2 _newPosition)
{
	position.x = _newPosition.x;
	position.y = _newPosition.y;
}


Transform::~Transform()
{
}
