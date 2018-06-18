#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void setPosition(glm::vec3 pos) { m_pos = pos; }
	void setFOV(float fov) { m_fov = fov; }
	void setFocalLength(float fl) { m_focalLength = fl; }
	void setAspectRatio(float ar) { m_aspectRatio = ar; }

	glm::vec3 getPosition() { return m_pos; }
	float getFOV() { return m_fov; }
	float getFocalLength() { return m_focalLength; }
	float getAspectRatio() { return m_aspectRatio; }

private:

	glm::vec3 m_pos;
	float m_fov;
	float m_focalLength;
	float m_aspectRatio;
};