#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setCameraSettings(float x, float y)
{
	m_aspectRatio = x / y;
	float theta = m_fov * M_PI / 180;
	float height = 2 * m_focalLength * tan((m_fov / 2) * M_PI / 180 ); 
	float width = m_aspectRatio * height;
	m_lowerLeft = glm::vec3(-width, -height, m_pos.z - m_focalLength);
	m_horizontal = glm::vec3(2 * width, 0.0, 0.0);
	m_vertical = glm::vec3(0.0, 2 * height, 0.0);
}