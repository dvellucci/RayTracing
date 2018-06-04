#include "Ray.h"

Ray::Ray(glm::vec3 origin, glm::vec3 rayDir)
{
	this->m_origin = origin;
	this->m_dir = rayDir;
}

Ray::~Ray()
{

}
