#include "Entity.h"

bool Entity::isActive() const
{
	if (m_alive)
		return true;
	else
		return false;
}