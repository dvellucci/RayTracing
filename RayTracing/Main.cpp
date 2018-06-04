#include "CImg.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "FileReader.h"
#include "Scene.h"
#include "Surface.h"
#include "RayTracer.h"
#include "Image.h"

glm::vec3 trace(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer, int depth);
glm::vec3 traceObjects(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer, 
	surface_data& data, int depth, float t_min, float t_max);
void renderScene(std::shared_ptr<Scene> scene);

int main()
{
	FileReader reader("test.txt");

	//set resolution
	int nx = 533;
	int ny = 400;

	//get the scene with all the object data
	auto scene = reader.setObjectData();

	//get the camera and set it's settings
//	auto camera = scene->m_camera;
//	camera->setCameraSettings(nx, ny);

	//get the raytracer
	auto rayTracer = std::make_shared<RayTracer>();

	//create file to write to
	std::ofstream myfile;
	myfile.open("example.txt");

	//generate the size of the image and the pixels
	//auto image = rayTracer->genImagePixels(scene, nx, ny);
	auto image = rayTracer->render(scene, nx, ny);

	//create CImg object
	cimg_library::CImg<float> cImage(image->m_width, image->m_height, 1, 3, 0);

	myfile << "P3\n" << nx << " " << ny << "\n255\n";
	//surface_data data;
	//for (int y = 0; y < image->m_height; y++)
	//{
	//	for (int x = 0; x < image->m_width; x++)
	//	{
	//		glm::vec3 col = glm::vec3(0, 0, 0);
	//		float u = float(x) / float(image->m_width);
	//		float v = float(y) / float(image->m_height);

	//		//create the ray at the pixel and do the trace
	//		//Ray ray(camera->m_pos, camera->m_lowerLeft + u * camera->m_horizontal + v * camera->m_vertical);
	//		auto ray = std::make_shared<Ray>(camera->m_pos, camera->m_lowerLeft + u * camera->m_horizontal + v * camera->m_vertical);
	//		col = rayTracer->trace(ray, scene, 0);
	//		//glm::vec3 col = traceObjects(ray, scene, rayTracer, data, 0, 0.0, FLT_MAX);
	//		//get rgb values
	//		int red = int(255 * col.x);
	//		int green = int(255 * col.y);
	//		int blue = int(255 * col.z);

	//		//set image colors
	//		cImage(x, y, 0, 0) = red;
	//		cImage(x, y, 0, 1) = green;
	//		cImage(x, y, 0, 2) = blue;
	//		myfile << red << " " << green << " " << blue << "\n";
	//	}
	//}

	for (int y = 0; y < image->m_height; y++)
	{

		for (int x = 0; x < image->m_width; x++)
		{
			int index = x + (y * image->m_width);
			float red = image->m_pixels[index]->m_color.r * 255;
			float green = image->m_pixels[index]->m_color.g * 255;
			float blue = image->m_pixels[index]->m_color.b * 255;

			cImage(x, y, 0, 0) = red;
			cImage(x, y, 0, 1) = green;
			cImage(x, y, 0, 2) = blue;
			myfile << red << " " << green << " " << blue << "\n";
		}
	}


	//cImage.rotate(180);
	cImage.save("scene.bmp");

	//render the image with CImg
	bool window = true;
	if (window)
	{
		cimg_library::CImgDisplay main_disp(cImage, "Ray Tracer");
		while (!main_disp.is_closed()) {
			main_disp.wait();
		}
	}

	return 0;
}

glm::vec3 trace(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer, int depth)
{
	surface_data data;

	if (rayTracer->trace(ray, scene, data, 0.0f, FLT_MAX))
	{
		if (depth < 50)
		{
			glm::vec3 intersection = ray.getOrigin() + data.m_t * ray.getDirection();
			glm::vec3 reflectDir = 2 * glm::dot(-ray.getDirection(), data.m_normal) * data.m_normal - (-ray.getDirection());
			glm::vec3 offsetOrig = intersection + 0.5f * reflectDir;
			Ray  reflectRay(offsetOrig, reflectDir);
			glm::vec3 color = (0.5f)*trace(reflectRay, scene, rayTracer, depth + 1);
			return color;
		}
		else
		{
			return glm::vec3(0, 0, 0);
		}
	
	}
	else
	{
		glm::vec3 unitDir = glm::normalize(ray.getDirection());
		float t = 0.5*(unitDir.y + 1.0);
		return (1.0f - t)*glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);

	}
}

glm::vec3 traceObjects(Ray& ray, std::shared_ptr<Scene>& scene, std::shared_ptr<RayTracer>& rayTracer, 
	surface_data& data, int depth, float t_min, float t_max)
{
	surface_data tempData;
	double closest = t_max;
	glm::vec3 color;
	if (depth > 2)
	{
		glm::vec3 unitDir = glm::normalize(ray.getDirection());
		float t = 0.5*(unitDir.y + 1.0);
		return (1.0f - t)*glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0);
	}

	//check sphere intersections
	for (int i = 0; i < scene->m_spheres.size(); i++)
	{
		if (scene->m_spheres[i]->hit(ray, t_min, closest, tempData))
		{
			closest = tempData.m_t;
			data = tempData;
			//glm::vec3 color = 0.5f*glm::vec3(data.m_normal.x + 1, data.m_normal.y + 1, data.m_normal.z + 1);
			//return color;
		}
	}

	glm::vec3 intersection = ray.getOrigin() + (float)closest * ray.getDirection();
	glm::vec3 reflectDir = 2 * glm::dot(-ray.getDirection(), data.m_normal) * data.m_normal - (-ray.getDirection());
	glm::vec3 offsetOrig = intersection + 0.1f * reflectDir;
	Ray * reflectRay = new Ray(offsetOrig, reflectDir);
	color = 0.5f * traceObjects(ray, scene, rayTracer, tempData, depth + 1, t_min, closest);
	return color;
}

void renderScene(std::shared_ptr<Scene> scene)
{

}
