#include "Plane.h"

Plane::Plane()
{
}

Plane::~Plane()
{
}

bool Plane::hit(std::shared_ptr<Ray> ray, float& t, glm::vec3& norm)
{
	float denom = glm::dot(m_normal, ray->getDirection());

	if (abs(denom) > 1e-6) 
	{

		t = glm::dot(m_point - ray->getOrigin(), m_normal) / denom;

		// Calculate normal
		norm = m_normal;

		return (t >= 0);
	}

	return false;
}
