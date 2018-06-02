#include "Sphere.h"

Sphere::Sphere() : m_center(0.0f, 0.0f, 0.0f), m_radius(0.0f)
{
}

Sphere::~Sphere()
{
}

//checks if a ray interesects with a sphere
bool Sphere::hit(const Ray & ray, float t_min, float t_max, surface_data& data) const
{
	glm::vec3 oc = ray.getOrigin() - m_center;
	float a = glm::dot(ray.getDirection(), ray.getDirection());
	float b = glm::dot(oc, ray.getDirection());
	float c = glm::dot(oc, oc) - m_radius* m_radius;
	float discriminant = b * b - 4 * a*c;

	if (discriminant < 0)
	{
		//solve the quadratic and set the t, point of intersection and normal of the intersection
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min) 
		{
			data.m_t = temp;
			data.m_point = ray.pointAtparameter(data.m_t);
			data.m_normal = (data.m_point - m_center) / m_radius;
			return true;
		}
		
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			data.m_t = temp;
			data.m_point = ray.pointAtparameter(data.m_t);
			data.m_normal = (data.m_point - m_center) / m_radius;
			return true;
		}
	}

	return false;
}
