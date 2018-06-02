#pragma once
#ifndef SURFACEH
#define SURFACEH
#include "Ray.h"

struct surface_data
{
	float m_t;
	glm::vec3 m_point;
	glm::vec3 m_normal;
};

class Surface
{
public:

	Surface() {} 
	~Surface() {}

	virtual bool hit(const Ray& ray, float t_min, float t_max, surface_data& data) const = 0;

	//light variables
	glm::vec3 ambColor;
	glm::vec3 difColor;
	glm::vec3 speColor;

private:
};

#endif