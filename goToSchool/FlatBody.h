#pragma once
#include "FlatVector.h"

enum ShapeType
{
	Circle = 0,
	Box = 1,
	Polygon = 2
};

class FlatBody
{
public:

	FlatVector position;
	FlatVector linearVelocity;
	float rotation;
	float rotationalVelocity;

	float density;
	float mass;
	float restitution;
	float area;

	bool isStatic;

	float radius;
	float width;
	float height;
	
	ShapeType shapeType;

	FlatBody(FlatVector position, float denstiny, float mass, float restitution, float area, bool isStatic, float radius
		, float width, float height, ShapeType shapeType)
	{
		this->position = position;
		this->density = density;
		this->mass = mass;
		this->restitution = restitution;
		this->area = area;
		this->isStatic = isStatic;
		this->radius = radius;
		this->width = width;
		this->height = height;
		this->shapeType = shapeType;
	}
	
	~FlatBody() {};

};

