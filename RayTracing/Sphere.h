#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Surface.h"
class Sphere : public Surface
{
public:
	Sphere();
	~Sphere();
	
	bool hit(const Ray& ray, float t_min, float t_max, surface_data& data) const;
	void setCenter(glm::vec3 center) { m_center = center; }
	void setRadius(float radius) { m_radius = radius; }
	float getRadius() const { return m_radius; }
	glm::vec3 getCenter() const { return m_center; }

private:
	float m_radius;
	glm::vec3 m_center;
	
};