#pragma once

namespace DirectXCore
{
	template <class T>
	class QuadTree
	{
	private:
		QuadTree* m_topLeftNode;
		QuadTree* m_topRightNode;
		QuadTree* m_bottomLeftNode;
		QuadTree* m_bottomRightNode;

		T* data;

	public:
		QuadTree();
		~QuadTree();

		QuadTree(const QuadTree& quadTree);
		QuadTree& operator=(const QuadTree& quadTree);
		
	};
}

