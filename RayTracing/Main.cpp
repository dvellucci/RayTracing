#include "stb_image.h"
#include "stb_image_write.h"
#include "CImg.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "FileReader.h"
#include "Scene.h"
#include "Surface.h"
#include "RayTracer.h"

glm::vec3 color(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer);

int main()
{
	FileReader reader("test.txt");

	//set resolution
	int nx = 400;
	int ny = 300;

	//get the scene with all the object data
	auto scene = reader.setObjectData();

	//get the camera and set it's settings
	auto camera = scene->m_camera;
	camera->setCameraSettings(nx, ny);

	//get the raytracer
	auto rayTracer = std::make_shared<RayTracer>();

	//create file to write to
	std::ofstream myfile;
	myfile.open("example.txt");

	myfile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray ray(camera->m_pos, camera->m_lowerLeft + u * camera->m_horizontal + v * camera->m_vertical);
			glm::vec3 col = color(ray, scene, rayTracer);
			int ir = int(255*col.x);
			int ig = int(255*col.y);
			int ib = int(255*col.z);
			myfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	//system("PAUSE");
	return 0;
}

glm::vec3 color(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer)
{
	surface_data data;
	if (rayTracer->sphereHit(ray, scene, data, 0.0f, FLT_MAX))
	{
		glm::vec3 color = 0.5f*glm::vec3(data.m_normal.x + 1, data.m_normal.y + 1, data.m_normal.z + 1);
		return color;
	}
	else
	{
		glm::vec3 unitDir = glm::normalize(ray.getDirection());
		float t = 0.5*(unitDir.y + 1.0);
		return (1.0f - t)*glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
	}
}
