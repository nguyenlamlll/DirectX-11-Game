#pragma once
#include "DirectXCore.h"

#define NOMINMAX


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
		bool Collided(BoundingBox* b1, BoundingBox* b2)
		{
			return b1->Intersects(*b2);
		}
	};
}