#pragma once

#define NOMINMAX
#include "DxBase.h"

namespace DirectXCore
{
	struct Box
	{
		// position of top-left corner
		float x, y;
		// dimensions
		float w, h;
		// velocity
		float vx, vy;
	};

	class PhysicsManager : public Singleton<PhysicsManager>
	{
	private:
		typedef std::vector<Rigidbody*> RigidbodyList;
		RigidbodyList* rigidbodies;

	public:
		const Vector3 gravity = Vector3(0, 9.81f, 0);

		PhysicsManager()
		{
			rigidbodies = new RigidbodyList();
		}
		~PhysicsManager()
		{

		}
		bool Update(float deltatime)
		{
			for (size_t i = 0; i < rigidbodies->size(); i++)
			{
				rigidbodies->at(i)->SetVelocity(gravity);
			}
			return true;
		}
		void RegisterRigidbody(Rigidbody* rigidbody)
		{
			rigidbodies->push_back(rigidbody);
		}
		float SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
		{
			float xInvEntry, yInvEntry;
			float xInvExit, yInvExit;

			// find the distance between the objects on the near and far sides for both x and y
			if (b1.vx > 0.0f)
			{
				xInvEntry = b2.x - (b1.x + b1.w);
				xInvExit = (b2.x + b2.w) - b1.x;
			}
			else
			{
				xInvEntry = (b2.x + b2.w) - b1.x;
				xInvExit = b2.x - (b1.x + b1.w);
			}

			if (b1.vy > 0.0f)
			{
				yInvEntry = b2.y - (b1.y + b1.h);
				yInvExit = (b2.y + b2.h) - b1.y;
			}
			else
			{
				yInvEntry = (b2.y + b2.h) - b1.y;
				yInvExit = b2.y - (b1.y + b1.h);
			}
			// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
			float xEntry, yEntry;
			float xExit, yExit;

			if (b1.vx == 0.0f)
			{
				xEntry = -std::numeric_limits<float>::infinity();
				xExit = std::numeric_limits<float>::infinity();
			}
			else
			{
				xEntry = xInvEntry / b1.vx;
				xExit = xInvExit / b1.vx;
			}

			if (b1.vy == 0.0f)
			{
				yEntry = -std::numeric_limits<float>::infinity();
				yExit = std::numeric_limits<float>::infinity();
			}
			else
			{
				yEntry = yInvEntry / b1.vy;
				yExit = yInvExit / b1.vy;
			}
			// find the earliest/latest times of collision
			float entryTime = (std::max)(xEntry, yEntry);
			float exitTime = (std::min)(xExit, yExit);

			// if there was no collision
			if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
			{
				normalx = 0.0f;
				normaly = 0.0f;
				return 1.0f;
			}
			else // if there was a collision
			{
				// calculate normal of collided surface
				if (xEntry > yEntry)
				{
					if (xInvEntry < 0.0f)
					{
						normalx = 1.0f;
						normaly = 0.0f;
					}
					else
					{
						normalx = -1.0f;
						normaly = 0.0f;
					}
				}
				else
				{
					if (yInvEntry < 0.0f)
					{
						normalx = 0.0f;
						normaly = 1.0f;
					}
					else
					{
						normalx = 0.0f;
						normaly = -1.0f;
					}
				}

				// return the time of collision
				return entryTime;
			}
		}
		float CheckSweptAABB(GameObject* obj1, GameObject* obj2, float& normalx, float& normaly)
		{
			Box* b1 = new Box();
			Box* b2 = new Box();

			b1->x = obj1->GetTransform()->GetPosition().x - obj1->GetTransform()->GetScale().x / 2;
			b1->y = obj1->GetTransform()->GetPosition().y - obj1->GetTransform()->GetScale().y / 2;
			b1->w = obj1->GetTransform()->GetScale().x;
			b1->h = obj1->GetTransform()->GetScale().y;

			b2->x = obj2->GetTransform()->GetPosition().x - obj2->GetTransform()->GetScale().x / 2;
			b2->y = obj2->GetTransform()->GetPosition().y - obj2->GetTransform()->GetScale().y / 2;
			b2->w = obj2->GetTransform()->GetScale().x;
			b2->h = obj2->GetTransform()->GetScale().y;

			if (!obj1->GetComponent<Rigidbody>()) b1->vx = b1->vy = 0;
			else
			{
				b1->vx = obj1->GetComponent<Rigidbody>()->GetVelocity().x;
				b1->vy = obj1->GetComponent<Rigidbody>()->GetVelocity().y;
			}
			if (!obj2->GetComponent<Rigidbody>()) b2->vx = b2->vy = 0;
			else
			{
				b2->vx = obj2->GetComponent<Rigidbody>()->GetVelocity().x;
				b2->vy = obj2->GetComponent<Rigidbody>()->GetVelocity().y;
			}

			return SweptAABB(*b1, *b2, normalx, normaly);
		}
		SimpleMath::Vector3 CheckBoundingBoxCollision(GameObject* obj1, GameObject* obj2)
		{
			Vector3 normal = Vector3(0, 0, 0);
			bool colType = obj1->GetComponent<Collider>()->GetCollider()->Intersects(*obj2->GetComponent<Collider>()->GetCollider());
			if (colType)
			{
				normal.z = 1;
				if (obj1->GetComponent<Rigidbody>())
				{
					float distanceX = obj1->GetTransform()->GetPosition().x - obj2->GetTransform()->GetPosition().x;
					float distanceY = obj1->GetTransform()->GetPosition().y - obj2->GetTransform()->GetPosition().y;
					float extentDistanceX = obj1->GetComponent<Collider>()->GetCollider()->Extents.x + obj2->GetComponent<Collider>()->GetCollider()->Extents.x;
					float extentDistanceY = obj1->GetComponent<Collider>()->GetCollider()->Extents.y + obj2->GetComponent<Collider>()->GetCollider()->Extents.y;

					if (abs(distanceX) < extentDistanceX)
					{
						/*if (abs(distanceX) < extentDistanceX * 9 / 10)
						{
							if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
								normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
							else if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
								normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
						}*/
						if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().y > 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().y > 0) && distanceY < 0)
							normal = (normal.y >= 0) ? normal + Vector3(0, -1, 0) : normal;
						else if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().y < 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().y < 0) && distanceY > 0)
							normal = (normal.y <= 0) ? normal + Vector3(0, 1, 0) : normal;
					}
					else;
					if (abs(distanceY) < extentDistanceY)
					{
						if (abs(distanceY) < extentDistanceY * 8.5f / 10)
						{
							if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().x > 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().x > 0) && distanceX < 0)
								normal = (normal.x >= 0) ? normal + Vector3(-1, 0, 0) : normal;
							else if ((obj1->GetComponent<Rigidbody>()->GetAcceleration().x < 0 || obj1->GetComponent<Rigidbody>()->GetMovingVector().x < 0) && distanceX > 0)
								normal = (normal.x <= 0) ? normal + Vector3(1, 0, 0) : normal;
						}
					}
					else;
				}
				/*obj1->OnCollisionEnter(obj2->GetComponent<Collider>(), normal);
				obj2->GetComponent<Collider>()->OnCollisionEnter(obj1->GetComponent<Collider>(), normal*-1);
				normal = Vector3(0, 0, 0);*/
			}
			return normal;
		}
		bool Collided(BoundingBox* b1, BoundingBox* b2)
		{
			return b1->Intersects(*b2);
		}
	};
}