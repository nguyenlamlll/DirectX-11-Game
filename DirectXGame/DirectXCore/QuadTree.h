#pragma once
#include "GameObject.h"

namespace DirectXCore
{
	class QuadTree
	{
	public:
		QuadTree();
		QuadTree(RECT* _mapSize, int _level, int _maximumLevel);
		~QuadTree();

		void Insert(GameObject* _object);
		void Insert(GameObject* _object,bool mobile);
		bool IsContain(Vector3 _position, Vector3 _scale);
		void UpdateWithCamera(Vector3 _position, Vector3 _scale, float _elapsedTime);
		std::vector<QuadTree*>* GetNodes() { return nodes; }
		void GetBranchNodesWithCamera(Vector3 _position, Vector3 _scale, float _elapsedTime, std::vector<GameObject*>* _objectLists);
		std::vector<GameObject*>* GameObjectList() { return objectList; }
		void ClearTree();
	private:
		void Split();
		int level, maximumLevel;
		RECT* region;
		std::vector<GameObject*>* objectList;
		//QuadTree** nodes;
		std::vector<QuadTree*>* nodes;
	};
}

