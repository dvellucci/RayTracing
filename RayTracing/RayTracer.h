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

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	std::shared_ptr<Image> genImagePixels(std::shared_ptr<Scene>& scene, int resW, int resH);

	static void traceSection(std::vector<std::shared_ptr<Pixel>> pixels, int start, int count, std::shared_ptr<Scene> scene);
	static glm::vec3 average(std::vector<glm::vec3> traces);
	static bool intersectSphere(std::shared_ptr<Ray> ray, std::shared_ptr<Sphere> sphere, float& t, glm::vec3 & norm);
	static bool solveQuadratic(const float & a, const float & b, const float & c, float & x0, float & x1);
	static glm::vec3 trace(std::shared_ptr<Ray> ray, std::shared_ptr<Scene> scene, int depth);
	static glm::vec3 lightColor(std::shared_ptr<Scene> scene, glm::vec3 intersection, std::shared_ptr<Surface> surface,
		glm::vec3 norm, glm::vec3 v);
	static glm::vec3 calculatePhong(std::shared_ptr<Light> light, std::shared_ptr<Ray> ray, 
		std::shared_ptr<Surface> surface, glm::vec3 norm, glm::vec3 v);
	static std::vector<std::shared_ptr<Ray>> generateRays(std::shared_ptr<Scene> scene, std::shared_ptr<Pixel> pixel);
	std::shared_ptr<Image> render(std::shared_ptr<Scene> scene,  int x, int y);

private:

};