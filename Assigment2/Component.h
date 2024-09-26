#pragma once
#include <SFML/Graphics.hpp>
#include "vec.h"

class Componet
{

};



class CTransform
{
public:
	CTransform() {}
	CTransform(const sf::Vector2f& p, const CVec2f& v, float a)
		: pos(p), velocity(v), angle(a) {}
	~CTransform() {}

public:
	sf::Vector2f pos = { 0.0f ,0.0f };
	CVec2f velocity = { 0.0f ,0.0f };
	float angle = .0;
};

class CShape
{
public:
	CShape() {}
	CShape(float radius, int vertex, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, vertex), radius(radius), points(vertex)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
	~CShape() {}

public:
	sf::CircleShape circle;
	float radius = .0;
	int points = 0;
	sf::Color fill;
	sf::Color outline;
	float thickness = 0;
};

class CCollision
{
public:
	CCollision() {}
	CCollision(float r) : radius(r) {}
	~CCollision() {}

public:
	float radius = .0;
};

class CScore
{
public:
	CScore() {}
	CScore(int score_in): score(score_in) {}
	~CScore() {}

public:
	int score = 0;

};

class CLifespan
{
public:
	CLifespan() {}
	CLifespan(int total) : remaining(total), total(total) {}
	~CLifespan() {}

public:
	int remaining = 0;
	int total = 0;
};

class CInput
{
public:
	CInput() {};
	~CInput() {};

public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;
};


