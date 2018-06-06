#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Surface.h"

class Plane : public Surface
{
public:
	Plane();
	~Plane();

	void setNormal(glm::vec3 n) { m_normal = n; }
	void setPoint(glm::vec3 p) { m_point = p; }

	glm::vec3 getNormal() { return m_normal; }
	glm::vec3 getPoint() { return m_point; }

	bool hit(std::shared_ptr<Ray> ray, float &t, glm::vec3& norm) override;

private:
	glm::vec3 m_normal;
	glm::vec3 m_point;
};