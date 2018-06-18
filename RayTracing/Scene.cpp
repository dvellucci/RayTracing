#include "Scene.h"

Scene::Scene() 
{

}

Scene::~Scene()
{

}

std::shared_ptr<Image> Scene::setUpScene(int heightResolution)
{
	std::vector<std::shared_ptr<Pixel>> pixels;

	float imagePlaneHeight = float(2.0f * m_camera->getFocalLength() * tan((m_camera->getFOV() / 2.0f) * M_PI / 180.0f));
	float imagePlaneWidth = m_camera->getAspectRatio() * imagePlaneHeight;

	int widthResolution = int(heightResolution * m_camera->getAspectRatio());

	float pixelWidth = imagePlaneWidth / widthResolution;
	float pixelHeight = imagePlaneHeight / heightResolution;

	//convert to world coordinates
	//credit: http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
	for (int y = 0; y < heightResolution; ++y)
	{
		for (int x = 0; x < widthResolution; ++x)
		{

			glm::vec3 pixelPosition = {
				(m_camera->getPosition().x - imagePlaneWidth / 2) + (pixelWidth / 2) + (x * pixelWidth),
				(m_camera->getPosition().y + imagePlaneHeight / 2) - (pixelHeight / 2) - (y * pixelHeight),
				m_camera->getPosition().z - m_camera->getFocalLength()
			};

			auto pixel = std::make_shared<Pixel>();
			pixel->m_pos = pixelPosition;
			pixels.push_back(pixel);
		}
	}

	auto image = std::make_shared<Image>(widthResolution, heightResolution, pixels);
	return image;
}

