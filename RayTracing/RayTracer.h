#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Ray.h"
#include "Scene.h"
#include "Surface.h"
#include "Sphere.h"
#include "Image.h"
#include <memory>
#include <iostream>

#define M_PI 3.14159265

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	//performs the tracing and checks for intersection of surfaces
	glm::vec3 trace(std::shared_ptr<Ray> ray, std::shared_ptr<Scene> scene, int depth);
	//used for multi threading to trace chunks of pixels in parallel
	void traceChunk(std::vector<std::shared_ptr<Pixel>> pixels, int start, int stride, std::shared_ptr<Scene> scene);

	//calculates the color of the surfaces
	glm::vec3 surfaceColor(std::shared_ptr<Scene> scene, glm::vec3 intersection, std::shared_ptr<Surface> surface,
		glm::vec3 norm, glm::vec3 rayDir);
	//calculates the phong lighting for each ray
	glm::vec3 calculatePhong(std::shared_ptr<Light> light, std::shared_ptr<Ray> ray, 
		std::shared_ptr<Surface> surface, glm::vec3 norm, glm::vec3 rayDir);
	//generates the ray and its direction from each pixel
	std::shared_ptr<Ray> generateRay(std::shared_ptr<Scene> scene, std::shared_ptr<Pixel> pixel);

private:

	std::shared_ptr<Ray> getReflectRay(glm::vec3 rayDirection, glm::vec3 intersection, glm::vec3 norm);
	float m_recursionDepth;
};