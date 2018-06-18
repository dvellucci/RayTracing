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
	float t0, t1;
	glm::vec3 oc = ray->getOrigin() - m_center;
	float a = glm::dot(ray->getDirection(), ray->getDirection());
	float b = 2 * glm::dot(oc, ray->getDirection());
	float c = glm::dot(oc, oc) - m_radius* m_radius;
	float discriminant = b * b - a*c;

	//stop if the quadratic cannot be solved
	if (!quadratic(a, b, c, t0, t1))
	{
		return false;
	}

	//make sure the closest intersection is used
	t = t0;

	norm = glm::normalize((ray->getOrigin() + t * ray->getDirection()) - m_center);

	return true;
}

//help for this function from http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
bool Sphere::quadratic(const float & a, const float & b, const float & c, float & t0, float & t1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0.0f) return false;
	else if (discr == 0.0f)
		t0 = t1 = -0.5f * b / a;
	else
	{
		float q = (b > 0.0f) ?
			-0.5f * (b + sqrt(discr)) :
			-0.5f * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}

	//make x0 the smaller value
	if (t0 > t1) std::swap(t0, t1);

	//if both t values are below zero, then return false
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return false;
	}

	return true;
}
