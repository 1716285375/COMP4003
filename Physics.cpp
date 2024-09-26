#include "Physics.h"


vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    // TODO: return the overlap rectangle size of the bounding boxes of entity a and b
	// bad implementation
	/*vec2 aPos = a->getComponent<CTransform>().prevPos;
	vec2 bPos = b->getComponent<CTransform>().prevPos;
	const vec2& aHalfSize = a->getComponent<CBoundingBox>().halfSize;
	const vec2& bHalfSize = b->getComponent<CBoundingBox>().halfSize;

	bool x_flag = (aPos.x - aHalfSize.x) <= (bPos.x + bHalfSize.x) && (aPos.x + aHalfSize.x) >= (bPos.x - bHalfSize.x);
	bool y_flag = (aPos.y - aHalfSize.y) <= (bPos.y + bHalfSize.y) && (aPos.y + aHalfSize.y) >= (bPos.y - bHalfSize.y);

	float x = 0.;
	float y = 0.;
	if (x_flag && y_flag)
	{
		if (aPos.x < bPos.x)
			x = (aPos.x + aHalfSize.x) - (bPos.x - bHalfSize.x);
		else
			x = (bPos.x + bHalfSize.x) - (aPos.x - aHalfSize.x);
		if (aPos.y < bPos.y)
			y = (aPos.y + aHalfSize.y) - (bPos.y - bHalfSize.y);
		else
			y = (bPos.y + bHalfSize.y) - (aPos.y - aHalfSize.y);
	}

	return vec2(x, y);*/

	vec2 aPos = a->getComponent<CTransform>().pos;
	vec2 bPos = b->getComponent<CTransform>().pos;
	const vec2& aHalfSize = a->getComponent<CBoundingBox>().halfSize;
	const vec2& bHalfSize = b->getComponent<CBoundingBox>().halfSize;

	return aHalfSize + bHalfSize - vec2(std::abs(aPos.x - bPos.x), std::abs(aPos.y - bPos.y));
}

vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b) {
    // TODO: return the previous overlap rectangle size of the bounding boxes of entity a and b
    //       previous overlap uses the entity's previous position
	// bad implementation
	/*vec2 aPos = a->getComponent<CTransform>().prevPos;
	vec2 bPos = b->getComponent<CTransform>().prevPos;
	const vec2& aHalfSize = a->getComponent<CBoundingBox>().halfSize;
	const vec2& bHalfSize = b->getComponent<CBoundingBox>().halfSize;

	bool x_flag = (aPos.x - aHalfSize.x) <= (bPos.x + bHalfSize.x) && (aPos.x + aHalfSize.x) >= (bPos.x - bHalfSize.x);
	bool y_flag = (aPos.y - aHalfSize.y) <= (bPos.y + bHalfSize.y) && (aPos.y + aHalfSize.y) >= (bPos.y - bHalfSize.y);

	float x = 0.;
	float y = 0.;
	if (x_flag && y_flag)
	{
		if (aPos.x < bPos.x)
			x = (aPos.x + aHalfSize.x) - (bPos.x - bHalfSize.x);
		else
			x = (bPos.x + bHalfSize.x) - (aPos.x - aHalfSize.x);
		if (aPos.y < bPos.y)
			y = (aPos.y + aHalfSize.y) - (bPos.y - bHalfSize.y);
		else
			y = (bPos.y + bHalfSize.y) - (aPos.y - aHalfSize.y);
	}

	return vec2(x, y);*/
	vec2 aPos = a->getComponent<CTransform>().prevPos;
	vec2 bPos = b->getComponent<CTransform>().prevPos;
	const vec2& aHalfSize = a->getComponent<CBoundingBox>().halfSize;
	const vec2& bHalfSize = b->getComponent<CBoundingBox>().halfSize;

	return aHalfSize + bHalfSize - vec2(std::abs(aPos.x - bPos.x), std::abs(aPos.y - bPos.y));
}
