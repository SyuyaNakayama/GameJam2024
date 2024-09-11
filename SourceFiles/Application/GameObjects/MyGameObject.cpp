#include "MyGameObject.h"

void MyGameObject::Initialize(const ObjectData& objData)
{
	sprite->size = objData.size;
	sprite->position.x = objData.posX;
	sprite->position.y = WristerEngine::WIN_SIZE.y - Const(float, "GroundHeight");
	sprite->anchorPoint = { 0.5f,1.0f };
}