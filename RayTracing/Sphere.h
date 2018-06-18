#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Surface.h"
class Sphere : public Surface
{
public:
	Sphere();
	~Sphere();
	
	void setCenter(glm::vec3 center) { m_center = center; }
	void setRadius(float radius) { m_radius = radius; }

	float getRadius() const { return m_radius; }
	glm::vec3 getCenter() const { return m_center; }

	bool hit(std::shared_ptr<Ray> ray, float &t, glm::vec3& norm) override;
	bool quadratic(const float & a, const float & b, const float & c, float & x0, float & x1);

private:

	float m_radius;
	glm::vec3 m_center;
};