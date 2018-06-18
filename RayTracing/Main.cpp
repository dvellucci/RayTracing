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

std::shared_ptr<Image> renderScene(const std::shared_ptr<Scene>& scene, const std::shared_ptr<RayTracer>& tracer, int heightResolution);

int main()
{
	int userOption = 0;
	std::string sceneFile = "";

	std::cout << "Pick a scene to render (Enter a number in the range [1, 5]: ";
	std::cin >> userOption;
	sceneFile = "scene" + std::to_string(userOption) + ".txt";
	FileReader reader("scene_data/"+ sceneFile);

	//height resolution
	int heightResolution = 400;

	//get the scene with all the object data
	//sets the camera and all the surface dimensions of each object in the scene
	auto scene = reader.setObjectData();

	//create the raytracer
	auto rayTracer = std::make_shared<RayTracer>();

	//generate the size of the image and the pixels
	auto image = renderScene(scene, rayTracer, heightResolution);

	//create CImg object
	cimg_library::CImg<float> cImage(image->m_width, image->m_height, 1, 3, 0);

	//read the pixels and generate the cImg image
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

	std::string savePath = "scene_renders/" + sceneFile + ".bmp";
	cImage.save(savePath.c_str());

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
std::shared_ptr<Image> renderScene(const std::shared_ptr<Scene>& scene, const std::shared_ptr<RayTracer>& tracer, int heightResolution)
{
	auto image = scene->setUpScene(heightResolution);
	int size = image->m_width * image->m_height;

	//generate the threads and call traceChunk for each run
	std::vector<std::thread> threads;
	int numOfThreads = 8;
	int chunk = size / numOfThreads;
	for (int i = 0; i < numOfThreads; i++)
	{
		threads.push_back(std::thread(&RayTracer::traceChunk, tracer, image->m_pixels, i * chunk, chunk, scene));
	}

	//run the generated threads
	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	return image;
}
