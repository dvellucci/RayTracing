#include "Sphere.h"

Sphere::Sphere() : m_center(0.0f, 0.0f, 0.0f), m_radius(0.0f)
{
}

Sphere::~Sphere()
{
}

//checks if a ray interesects with a sphere
bool Sphere::hit(std::shared_ptr<Ray> ray, float &t, glm::vec3& norm) 
{
	float x0, x1;
	glm::vec3 oc = ray->getOrigin() - m_center;
	float a = glm::dot(ray->getDirection(), ray->getDirection());
	float b = 2 * glm::dot(oc, ray->getDirection());
	float c = glm::dot(oc, oc) - m_radius* m_radius;
	float discriminant = b * b - a*c;

	//stop if the quadratic cannot be solved
	if (!quadratic(a, b, c, x0, x1))
	{
		return false;
	}

	t = x0;

	norm = glm::normalize((ray->getOrigin() + t * ray->getDirection()) - m_center);

	return true;
}
