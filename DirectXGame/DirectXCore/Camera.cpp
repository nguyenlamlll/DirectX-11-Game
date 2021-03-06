#include "stdafx.h"
#include "Camera.h"

using namespace DirectXCore;

Camera::Camera()
{
}

Camera::Camera(int _x, int _y)
{
	this->SetPosition(DirectX::SimpleMath::Vector3(_x, _y, 1));
	this->SetViewPort(0, 0, _x * 2, _y * 2);
}

void Camera::SetPosition(int _x, int _y)
{
	camPosition.x = _x;
	camPosition.y = _y;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left = camPosition.x - camViewport.Width / 2;
	bound.right = bound.left + camViewport.Width;
	bound.top = camPosition.y - camViewport.Height / 2;
	bound.bottom = bound.top + camViewport.Height;

	return bound;
}


bool Camera::IsContain(DirectX::SimpleMath::Vector3 _objectPosition, DirectX::SimpleMath::Vector3 _objectScale)
{
	bool notContainX = (_objectPosition.x + _objectScale.x<0 || _objectPosition.x - _objectScale.x>camViewport.Width);
	bool notContainY = (_objectPosition.y + _objectScale.y<0 || _objectPosition.y - _objectScale.y>camViewport.Height);
	// To be contained, both X and Y of an object must be within viewport.
	// !notContainX is ContainX and so on with Y.
	bool iscontain = !notContainX && !notContainY;
	return iscontain;
}


void Camera::SetViewPort(int _upperX, int _upperY, int _wid, int _hei)
{
	camViewport.Width = _wid;
	camViewport.Height = _hei;
	camViewport.TopLeftX = _upperX;
	camViewport.TopLeftY = _upperY;
	camViewport.MinDepth = 0;
	camViewport.MaxDepth = 1;
}

void Camera::InitializeOthoMatrix(int _wid, int _hei, float _near, float _far)
{
}

void Camera::InitializeProjectionMatrix(float _fov, float _aspect, float _near, float _far)
{
}

Camera::~Camera()
{
}
