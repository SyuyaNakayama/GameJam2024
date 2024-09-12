#include "BaseEnemy.h"

void BaseEnemy::OnCollision(WristerEngine::_2D::ColliderGroup* collider)
{
	for (auto pair : collisionPair[0])
	{
		if (collider->GetColliderName(pair) == "attack")
		{
			hpRate -= 0.01f;
		}
	}
}