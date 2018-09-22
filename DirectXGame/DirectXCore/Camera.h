#include "stdafx.h"

#pragma once
class Camera
{
public:
	Camera(int _wid, int _hei);
	void SetPosition(int _x, int _y);
	void SetPosition(DirectX::SimpleMath::Vector2 _pos) { camPosition = _pos; }
	DirectX::SimpleMath::Vector2 GetPosition() { return camPosition; }
	
	RECT GetBound();

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	~Camera();
private:
	DirectX::SimpleMath::Vector2 camPosition;
	int width, height;
};

