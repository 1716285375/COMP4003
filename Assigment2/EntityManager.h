#pragma once

#include "Entity.h"
class EntityManager
{
	EntityVec	m_entities;
	EntityVec	m_toAdd;
	EntityMap	m_entityMap;
	size_t		m_totalEntities = 0;

public:
	EntityManager() {}
	void update();
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	EntityVec& getEntities();
	EntityVec& getEntities(const std::string& tag);
	void removeDeadEntities(EntityVec& vec);

};

