#pragma once

#include "stdafx.h"
#include "Sprite.h"

class Animation
{
public:
	Animation();
	Animation(int _rows, int _collums, Sprite _sprite);
	~Animation();
private:
	int frames;
};

