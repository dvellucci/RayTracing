#include "Plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
}

//help for this function from http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
bool Plane::hit(std::shared_ptr<Ray> ray, float& t, glm::vec3& norm)
{
	float denom = glm::dot(m_normal, ray->getDirection());

	//1e-6 is used to check if the denominator is a very small value above zero
	if (abs(denom) > 1e-6) 
	{

		t = glm::dot(m_point - ray->getOrigin(), m_normal) / denom;

		// Calculate normal
		norm = m_normal;

		if (t >= 0)
			return denom;
	}

	return false;
}
