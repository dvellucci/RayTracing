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


	virtual bool hit(const Ray& ray, float t_min, float t_max, surface_data& data) const = 0;

	//light variables
	glm::vec3 m_ambColor;
	glm::vec3 m_diffColor;
	glm::vec3 m_specColor;

private:
};

#endif