#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ray
{
public:
	Ray(glm::vec3 origin, glm::vec3 rayDir);
	~Ray();

	glm::vec3 getOrigin() const { return m_origin; }
	glm::vec3 getDirection() const { return m_dir; }
	glm::vec3 pointAtparameter(float t) const { return m_origin + t * m_dir; }

	glm::vec3 m_origin;
	glm::vec3 m_dir;
private:

};