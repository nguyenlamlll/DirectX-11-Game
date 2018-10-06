#include "stdafx.h"
#include "Object.h"

using namespace DirectXCore;

DirectXCore::Object::Object() 
{
	transform = new Transform(Vector2(0,0),Vector2(0,0),Vector2(1,1));
}

Object::~Object()
{
}
