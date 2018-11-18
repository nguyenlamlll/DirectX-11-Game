#include "stdafx.h"
#include "Transform.h"

using namespace DirectXCore;

Transform::Transform()
{
}

Transform::Transform(Vector3 _pos = Vector3(0,0,0), Vector3 _rot = Vector3(0,0,0), Vector3 _scl = Vector3(1,1,1))
{
	SetPosition(_pos);
	SetRotation(_rot);
	SetScale(_scl);
}

void Transform::SetWorldToScreenPosition(Vector3 _cameraShift) {
	screenPosition = position + _cameraShift;
}

void Transform::SetPosition(Vector3 _newPosition)
{
	position.x = _newPosition.x;
	position.y = _newPosition.y;
}

void DirectXCore::Transform::SetRotation(Vector3 _newRotation)
{
	rotation.x = _newRotation.x;
	rotation.y = _newRotation.y;
	rotation.z = _newRotation.z;
}
void Transform::SetScreenScale(Vector3 _newScreenScale)
{
	screenScale.x = _newScreenScale.x;
	screenScale.y = _newScreenScale.y;
	screenScale.z = _newScreenScale.z;
}
void Transform::SetScale(Vector3 _newScale) {
	scale.x = _newScale.x;
	scale.y = _newScale.y;
	scale.z = _newScale.z;
}

Transform::~Transform()
{
}
