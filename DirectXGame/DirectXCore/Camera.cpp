#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(int _x, int _y)
{
	this->SetPosition(DirectX::SimpleMath::Vector2(_x, _y));
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


bool Camera::IsContain(DirectX::SimpleMath::Vector2 _objectPosition)
{
	bool containX = (_objectPosition.x<0 || _objectPosition.x>camViewport.Width);
	bool containY = (_objectPosition.y<0 || _objectPosition.y>camViewport.Height);
	bool iscontain = !(containX || containY);
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
