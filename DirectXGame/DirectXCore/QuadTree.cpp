#include "stdafx.h"
#include "QuadTree.h"

using namespace DirectXCore;

template <class T>
QuadTree<T>::QuadTree():
	m_topLeftNode(nullptr),
	m_topRightNode(nullptr),
	m_bottomLeftNode(nullptr),
	m_bottomRightNode(nullptr)
{

}

template <class T>
QuadTree<T>::~QuadTree()
{
}

template<class T>
DirectXCore::QuadTree<T>::QuadTree(const QuadTree & quadTree)
{
}

template<class T>
QuadTree<T> & DirectXCore::QuadTree<T>::operator=(const QuadTree & quadTree)
{
	// TODO: insert return statement here
}
