#include "stdafx.h"
#include "QuadTree.h"

using namespace DirectXCore;

DirectXCore::QuadTree::QuadTree()
{
}

DirectXCore::QuadTree::QuadTree(RECT * _mapSize, int _level, int _maximumLevel)
{
	region = _mapSize;
	level = _level;
	maximumLevel = _maximumLevel;
	objectList = new std::vector<GameObject*>;
	Split();
}

DirectXCore::QuadTree::~QuadTree()
{
}

void DirectXCore::QuadTree::Insert(GameObject * _object)
{
	if (nodes)
	{
		if (nodes->at(0)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(0)->Insert(_object);
		if (nodes->at(1)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(1)->Insert(_object);
		if (nodes->at(2)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(2)->Insert(_object);
		if (nodes->at(3)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(3)->Insert(_object);
	}
	if (this->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
		objectList->push_back(_object);
}

bool DirectXCore::QuadTree::IsContain(Vector3 _position, Vector3 _scale)
{
	bool notContainX = (_position.x + _scale.x<region->left || _position.x - _scale.x>region->right);
	bool notContainY = (_position.y + _scale.y<region->top || _position.y - _scale.y>region->bottom);
	// To be contained, both X and Y of an object must be within viewport.
	// !notContainX is ContainX and so on with Y.
	bool iscontain = !notContainX && !notContainY;
	return iscontain;
}

void DirectXCore::QuadTree::UpdateWithCamera(Vector3 _position, Vector3 _scale,float _elapsedTime)
{
	if (nodes == NULL && IsContain(_position, _scale)) {
		for (size_t i = 0; i < this->objectList->size(); i++) this->objectList->at(i)->Update(_elapsedTime);
		
	}
}



void DirectXCore::QuadTree::Split()
{
	if (level != maximumLevel)
	{
		nodes = new std::vector<QuadTree*>;
		RECT* rect1 = new RECT(), *rect2 = new RECT(), *rect3 = new RECT, *rect4 = new RECT();
		rect1->left = rect3->left = region->left;
		rect1->right = rect3->right = rect2->left = rect4->left = region->right / 2 ;
		rect2->right = rect4->right = region->right;

		rect1->top = rect2->top = region->top;
		rect1->bottom = rect2->bottom = rect3->top = rect4->top = region->bottom / 2 ;
		rect3->bottom = rect4->bottom = region->bottom;

		nodes->push_back(new QuadTree(rect1, level + 1, maximumLevel));
		nodes->push_back(new QuadTree(rect2, level + 1, maximumLevel));
		nodes->push_back(new QuadTree(rect3, level + 1, maximumLevel));
		nodes->push_back(new QuadTree(rect4, level + 1, maximumLevel));
	}
	else nodes = NULL;
}
