#include "stdafx.h"
#include "Camera.h"


Camera::Camera(int _wid, int _hei)
{
	width = _wid;
	height = _hei;
	camPosition = DirectX::SimpleMath::Vector2(0, 0);
}

void Camera::SetPosition(int _x, int _y)
{
	camPosition.x = _x;
	camPosition.y = _y;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = camPosition.x - width / 2;
	bound.right = bound.left + width;;
	bound.top = camPosition.y - height / 2;
	bound.bottom = bound.top + height;

	return bound;
}


Camera::~Camera()
{
}
