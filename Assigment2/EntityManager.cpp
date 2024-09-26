#include "EntityManager.h"





/*
//std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
//{
//	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
//	m_entities.push_back(e);
//	m_entityMap[tag].push_back(e);
//	return e;
//}

//std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
//{
//	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
//	m_toAdd.push_back(e);
//	return e;
//}
*/


// 只能使用EntityManager来添加Entity，禁止其他任何方式来添加Entity
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto e = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_toAdd.push_back(e);
	return e;
}

EntityVec& EntityManager::getEntities()
{
	return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}

void EntityManager::update()
{
	//std::cout << m_totalEntities << std::endl;
	for (auto e : m_toAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	removeDeadEntities(m_entities);

	// C++17
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
	m_toAdd.clear();


}

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// according to the function of isActive() to judge
	for (auto& e : vec)
	{
		// 生命值 < 0 时，应销毁
		if (e->cLifespan->remaining <= 0)
		{
			e->cLifespan->remaining = 0;
			e->destroy();
		}
			


	}

	// 若已经死亡，应立即清除

	//std::cout << e->tag() << " " << e->id() << std::endl;
	//auto old_size = vec.size();
	//auto to_delete = std::remove_if(vec.begin(), vec.end(), [](const auto& e) {
	//	return !e->isActive(); });
	//vec.erase(to_delete, vec.end());
	//auto new_size = vec.size();
	//m_totalEntities -= (new_size - old_size);
	for (auto it = vec.begin(); it != vec.end(); )
	{
		if (!(*it)->isActive())
		{
			it = vec.erase(it);
			if (m_totalEntities > 1)
				--m_totalEntities;
		}
		else {
			++it;
		}
	}
}