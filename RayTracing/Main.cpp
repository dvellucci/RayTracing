#include "CImg.h"
#include <iostream>
#include <fstream>
#include "Ray.h"
#include "FileReader.h"
#include "Scene.h"
#include "Surface.h"
#include "RayTracer.h"
#include "Image.h"

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
	auto image = rayTracer->render(scene, nx, ny);

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
