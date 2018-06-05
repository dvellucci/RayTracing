#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light() {};
	~Light() {};

	void setPosition(glm::vec3 pos) { m_pos = pos; }
	void setColor(glm::vec3 color) { m_color = color; }

	glm::vec3 getPosition() { return m_pos; }
	glm::vec3 getColor() { return m_color; }

private:

	glm::vec3 m_pos;
	glm::vec3 m_color;
};