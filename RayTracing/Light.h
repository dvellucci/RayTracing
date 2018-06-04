#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light() {};
	~Light() {};

	glm::vec3 m_pos;
	glm::vec3 m_color;
private:
};