#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Component.h"


// auto e = std::shared_ptr<Entity>(new Entity(args));
class EntityManager;
class Entity
{
private:
	friend class EntityManager;

	Entity() {}
	Entity(const std::string& tag, size_t id) : m_tag(tag), m_id(id) {}

public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;

private:
	bool isActive() const;
	const std::string& tag() { return m_tag; }
	const size_t id() { return m_id; }
	void destroy() { m_alive = false; }

private:
	const size_t				m_id = 0;
	const std::string			m_tag = "Default";
	bool						m_alive = true;
};

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map   <std::string, EntityVec> EntityMap;