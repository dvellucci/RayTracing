#pragma once
#include <vector>
#include <memory>
#include "Sphere.h"
#include "Camera.h"
class Scene
{
public:
	Scene();
	~Scene();

	std::shared_ptr<Camera> m_camera;
	std::vector<std::shared_ptr<Sphere>> m_spheres;

private:

};