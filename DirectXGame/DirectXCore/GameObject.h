#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"

namespace DirectXCore
{
	class GameObject:public Object
	{
	public:
		GameObject();
		virtual void PreUpdate(float _deltaTime);
		virtual void Update(float _deltaTime);
		virtual void LateUpdate(float _deltaTime);
		virtual void Render();
		GameObject* GetGameObject() { return this; }
		Transform* GetTransform() { return transform; }
		std::string GetTag() { return tag; }
		void SetTag(std::string _newTag) {  tag = _newTag; }
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
			ReferenceGameObject();
		}
		virtual void OnCollisionEnter();
		~GameObject();
	protected:
		std::string tag;
		Transform* transform;
		std::vector<Component*>* componentList;
	private:
		void ReferenceGameObject();
	};
}

