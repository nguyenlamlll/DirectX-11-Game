#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Transform.h"

namespace DirectXCore
{
	class GameObject:public Object
	{
	public:
		GameObject();
		virtual void Update();
		virtual void Render();
		BoundingBox* GetBoxCollider() { return boxCollider; }
		Transform* GetTransform() { return transform; }
		template<class ComponentType>	ComponentType* GetComponent() {
			for (size_t i = 0; i < componentList->size(); i++)
			{
				if (ComponentType* compo = dynamic_cast<ComponentType*>(componentList->at(i))) return compo;
			}
			return nullptr;
		}
		template<class ComponentType>	void AddComponent(ComponentType *_component) {
			for (size_t i = 0; i < componentList->size(); i++)
			{
				if (ComponentType* compo = dynamic_cast<ComponentType*>(componentList->at(i))) return ;
			}
			componentList->push_back(_component);
		}
		virtual void OnCollisionEnter();
		~GameObject();
	protected:
		BoundingBox* boxCollider;
		Transform* transform;
		std::vector<Component*>* componentList;
	private:
	};
}

