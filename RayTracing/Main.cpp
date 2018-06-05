#include "CImg.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "FileReader.h"
#include "Scene.h"
#include "Surface.h"
#include "RayTracer.h"
#include "Image.h"
#include <chrono>
#include <thread>
#include <mutex>

std::shared_ptr<Image> renderScene(std::shared_ptr<Scene> scene, std::shared_ptr<RayTracer> tracer, int x, int y);

int main()
{
	FileReader reader("test.txt");

	//set resolution
	int nx = 533;
	int ny = 400;

	//get the scene with all the object data
	//sets the camera and all the surface dimensions of each object in the scene
	auto scene = reader.setObjectData();

	//create the raytracer
	auto rayTracer = std::make_shared<RayTracer>();

	//generate the size of the image and the pixels
	auto image = renderScene(scene, rayTracer, nx, ny);

	//create CImg object
	cimg_library::CImg<float> cImage(image->m_width, image->m_height, 1, 3, 0);

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
		}
	}

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

//render the scene with multi threading
std::shared_ptr<Image> renderScene(std::shared_ptr<Scene> scene, std::shared_ptr<RayTracer> tracer, int x, int y)
{
	auto image = tracer->genImagePixels(scene, x, y);
	int size = image->m_width * image->m_height;

	std::thread t0(&RayTracer::traceSection, tracer, image->m_pixels, 0, size / 8, scene);
	std::thread t1(&RayTracer::traceSection, tracer, image->m_pixels, size / 8, size / 8, scene);
	std::thread t2(&RayTracer::traceSection, tracer, image->m_pixels, size / 4, size / 8, scene);
	std::thread t3(&RayTracer::traceSection, tracer, image->m_pixels, 3 * size / 8, size / 8, scene);
	std::thread t4(&RayTracer::traceSection, tracer, image->m_pixels, size / 2, size / 8, scene);
	std::thread t5(&RayTracer::traceSection, tracer, image->m_pixels, 5 * size / 8, size / 8, scene);
	std::thread t6(&RayTracer::traceSection, tracer, image->m_pixels, 3 * size / 4, size / 8, scene);
	std::thread t7(&RayTracer::traceSection, tracer, image->m_pixels, 7 * size / 8, size / 8, scene);
	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();

	return image;
}
