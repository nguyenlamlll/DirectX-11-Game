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
	nodes = new std::vector<QuadTree*>;
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
	else if (this->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))	objectList->push_back(_object);
}

void DirectXCore::QuadTree::Insert(GameObject * _object, bool mobile)
{
	if (nodes)
	{
		if (mobile || nodes->at(0)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(0)->Insert(_object, mobile);
		if (mobile || nodes->at(1)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(1)->Insert(_object, mobile);
		if (mobile || nodes->at(2)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(2)->Insert(_object, mobile);
		if (mobile || nodes->at(3)->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale()))
			nodes->at(3)->Insert(_object, mobile);
	}
	else if (mobile || this->IsContain(_object->GetTransform()->GetPosition(), _object->GetTransform()->GetScale())) 	objectList->push_back(_object);
}

bool DirectXCore::QuadTree::IsContain(Vector3 _position, Vector3 _scale)
{
	bool notContainX = (_position.x + _scale.x<this->region->left || _position.x - _scale.x>this->region->right);
	bool notContainY = (_position.y + _scale.y<this->region->top || _position.y - _scale.y>this->region->bottom);
	// To be contained, both X and Y of an object must be within viewport.
	// !notContainX is ContainX and so on with Y.
	bool iscontain = !notContainX && !notContainY;
	return iscontain;
}

void DirectXCore::QuadTree::UpdateWithCamera(Vector3 _position, Vector3 _scale, float _elapsedTime)
{
	if (nodes == NULL && IsContain(_position, _scale)) {
		for (size_t i = 0; i < this->objectList->size(); i++) this->objectList->at(i)->Update(_elapsedTime);
	}
}

void DirectXCore::QuadTree::GetBranchNodesWithCamera(Vector3 _position, Vector3 _scale, float _elapsedTime, std::vector<GameObject*>* _objectLists)
{
	//Vector3 regionVec = Vector3(_node->region->right - _node->region->left, _node->region->bottom - _node->region->top, 0);
	if (this->nodes == NULL && this->IsContain(_position, _scale)) {
		_objectLists->insert(_objectLists->end(), this->objectList->begin(), this->objectList->end());
		//return;
	}
	else if (this->nodes != NULL)
	{
		this->nodes->at(0)->GetBranchNodesWithCamera(_position, _scale, _elapsedTime, _objectLists);
		this->nodes->at(1)->GetBranchNodesWithCamera(_position, _scale, _elapsedTime, _objectLists);
		this->nodes->at(2)->GetBranchNodesWithCamera(_position, _scale, _elapsedTime, _objectLists);
		this->nodes->at(3)->GetBranchNodesWithCamera(_position, _scale, _elapsedTime, _objectLists);
	}
}

void DirectXCore::QuadTree::ClearTree()
{
	if (this->nodes == NULL) {
		objectList->clear();
	}
	else
	{
		this->nodes->at(0)->ClearTree();
		this->nodes->at(1)->ClearTree();
		this->nodes->at(2)->ClearTree();
		this->nodes->at(3)->ClearTree();
		/*	ClearTree(this->nodes->at(0));
			ClearTree(this->nodes->at(1));
			ClearTree(this->nodes->at(2));
			ClearTree(this->nodes->at(3));*/
	}
}



void DirectXCore::QuadTree::Split()
{
	if (this->level < this->maximumLevel)
	{
		LONG rectWidth = this->region->right - this->region->left;
		LONG rectHeight = this->region->bottom - this->region->top;
		RECT* rect1 = new RECT(), *rect2 = new RECT(), *rect3 = new RECT, *rect4 = new RECT();
		rect1->left = rect3->left = this->region->left;
		rect1->right = rect3->right = rect2->left = rect4->left = rect1->left + rectWidth / 2;
		rect2->right = rect4->right = this->region->right;

		rect1->top = rect2->top = this->region->top;
		rect1->bottom = rect2->bottom = rect3->top = rect4->top = rect1->top + rectHeight / 2;
		rect3->bottom = rect4->bottom = this->region->bottom;

		if (rect1->bottom - rect1->top == 2048)
			int a = 1;

		this->nodes->push_back(new QuadTree(rect1, this->level + 1, this->maximumLevel));
		this->nodes->push_back(new QuadTree(rect2, this->level + 1, this->maximumLevel));
		this->nodes->push_back(new QuadTree(rect3, this->level + 1, this->maximumLevel));
		this->nodes->push_back(new QuadTree(rect4, this->level + 1, this->maximumLevel));
	}
	else
	{
		this->nodes = NULL;
	}

}
