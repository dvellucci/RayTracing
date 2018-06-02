#include "RayTracer.h"

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

bool RayTracer::sphereHit(const Ray& ray, std::shared_ptr<Scene> scene, surface_data& data, float t_min, float t_max)
{
	surface_data tempData;
	double closest = t_max;
	bool hit = false;
	//check for sphere hit
	for (int i = 0; i < scene->m_spheres.size(); i++)
	{
		if (scene->m_spheres[i]->hit(ray, t_min, closest, tempData))
		{
			hit = true;
			closest = tempData.m_t;
			data = tempData;
		}
	}
	return hit;
}

glm::vec3 RayTracer::trace(const Ray & ray, std::shared_ptr<Scene> scene, surface_data& data)
{
	surface_data tempData;
	float t_min = 0.0, t_max = FLT_MAX;
	double closest = t_max;

	for (int i = 0; i < scene->m_spheres.size(); i++)
	{
		if (scene->m_spheres[i]->hit(ray, t_min, closest, tempData))
		{

		}
	}
	return glm::vec3();
}
