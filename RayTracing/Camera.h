#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159265

class Camera
{
public:
	Camera();
	~Camera();

	void setCameraSettings(float x, float y);

	glm::vec3 m_pos;
	float m_fov;
	float m_focalLength;
	float m_aspectRatio;

	glm::vec3 m_lowerLeft, m_horizontal, m_vertical;
	glm::vec3 u, v, w;
private:
};