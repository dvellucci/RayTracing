#pragma once
#include <vector>
#include <memory>
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"
#include "Image.h"

#define M_PI 3.14159265

class Scene
{
public:
	Scene();
	~Scene();

	std::shared_ptr<Image> setUpScene(int heightResolution);

	std::shared_ptr<Camera> m_camera;
	std::vector<std::shared_ptr<Sphere>> m_spheres;
	std::vector<std::shared_ptr<Plane>> m_planes;
	std::vector<std::shared_ptr<Light>> m_lights;
private:

};