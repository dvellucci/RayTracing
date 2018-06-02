#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Ray.h"
#include "Scene.h"
#include "Surface.h"
#include "Sphere.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	bool sphereHit(const Ray& ray, std::shared_ptr<Scene> scene, surface_data& data, float t_min, float t_max);
	glm::vec3 trace(const Ray& ray, std::shared_ptr<Scene> scene, surface_data& data);

private:

};