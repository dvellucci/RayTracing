#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Pixel
{
public:
	Pixel() : m_pos(glm::vec3(0.0f, 0.0f, 0.0f)) {};
	~Pixel() {};

	glm::vec3 m_pos;
	glm::vec3 m_color;
private:
};