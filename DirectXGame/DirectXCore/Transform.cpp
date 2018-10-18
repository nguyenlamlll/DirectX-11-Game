#include "stdafx.h"
#include "Transform.h"

using namespace DirectXCore;

Transform::Transform()
{
}

Transform::Transform(Vector3 _pos = Vector3(0,0,1), Vector3 _rot = Vector3(0,0,1), Vector3 _scl = Vector3(1,1,1))
{
	position = _pos;
	rotation = _rot;
	scale = _scl;
}

void Transform::SetPosition(Vector3 _newPosition)
{
	position.x = _newPosition.x;
	position.y = _newPosition.y;
}


Transform::~Transform()
{
}
