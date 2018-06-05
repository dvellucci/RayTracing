#include "RayTracer.h"
#include <chrono>
#include <thread>
#include <mutex>

std::mutex mtx;

#define EPSILON 0.000001
#define DMAX 2

RayTracer::RayTracer()
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::traceSection(std::vector<std::shared_ptr<Pixel>> pixels, int start, int count, std::shared_ptr<Scene> scene)
{
	for (int i = start; i < start + count; ++i)
	{
		std::vector<std::shared_ptr<Ray>> rays = generateRays(scene, pixels[i]);
		std::vector<glm::vec3> traces;

		for (auto ray : rays)
		{
			traces.push_back(trace(ray, scene, 0));
		}


		pixels[i]->m_color = average(traces);
	}
}

glm::vec3 RayTracer::average(std::vector<glm::vec3> traces)
{
	float r = 0.0f, g = 0.0f, b = 0.0f;
	for (auto trace : traces) {
		r += trace.r;
		g += trace.g;
		b += trace.b;
	}
	int s = traces.size();
	r /= s;
	g /= s;
	b /= s;
	return glm::vec3(r, g, b);
}

bool RayTracer::solveQuadratic(const float & a, const float & b, const float & c, float & x0, float & x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	if (x0 < 0) {
		x0 = x1; 
		if (x0 < 0) return false; 
	}

	return true;
}

glm::vec3 RayTracer::trace(std::shared_ptr<Ray> ray, std::shared_ptr<Scene> scene, int depth)
{
	if (depth > DMAX)
		return scene->backgroundColor;

	float t;
	float tmin = FLT_MAX;
	glm::vec3 n, norm;
	std::shared_ptr<Surface> surface;

	for(int i = 0, m = scene->m_spheres.size(); i < m; ++i)
	{
		auto sphere = scene->m_spheres[i];
		if (sphere->hit(ray, t, n))
		{
			if (t < tmin)
			{
				tmin = t;
				norm = n;
				surface = scene->m_spheres[i];
			}
		}
	}

	if (abs(tmin - FLT_MAX) < EPSILON) 
	{
		return scene->backgroundColor;
	}

	glm::vec3 intersection = ray->m_origin + tmin * ray->m_dir;

	glm::vec3 color = lightColor(scene, intersection, surface, norm, -ray->getDirection());

	return color;
}

glm::vec3 RayTracer::lightColor(std::shared_ptr<Scene> scene, glm::vec3 intersection, std::shared_ptr<Surface> surface,
	glm::vec3 norm, glm::vec3 rayDir)
{		
	glm::vec3 color = surface->getAmbience();
	for (auto light : scene->m_lights)
	{
		float t;
		float tmin = glm::distance(light->getPosition(), intersection);
		glm::vec3 n;
		bool shadowed = false;
		glm::vec3 shadowDir = glm::normalize(light->getPosition() - intersection);

		float o = 0.1;
		glm::vec3 origOffset = o * shadowDir;

		auto ray = std::make_shared<Ray>(intersection + origOffset, shadowDir);

		for (int i = 0; i < scene->m_spheres.size(); ++i) 
		{
			auto sphere = scene->m_spheres[i];
			if (sphere->hit(ray, t, n)) 
			{
				if (t < tmin) 
				{
					shadowed = true;
					break;
				}
			}
		}

		//calculate phong lighting
		if (!shadowed)
		{
			color += calculatePhong(light, ray, surface, norm, rayDir);
		}

	}

	return color;
}

glm::vec3 RayTracer::calculatePhong(std::shared_ptr<Light> light, std::shared_ptr<Ray> ray,
	std::shared_ptr<Surface> surface, glm::vec3 norm, glm::vec3 rayDir)
{
	glm::vec3 l_vector = ray->getDirection();
	glm::vec3 reflectionVector = 2 * glm::dot(l_vector, norm) * norm - l_vector;

	float ldotn = glm::dot(l_vector, norm);
	float reflectDot = glm::dot(reflectionVector, rayDir);

	glm::vec3 spec = surface->getSpecular() * pow(glm::max(0.0f, reflectDot), surface->getShiny());
	glm::vec3 dif = surface->getDiffuse() * abs(ldotn);

	glm::vec3 color = light->getColor() * (dif + spec);

	return color; 
}

std::vector<std::shared_ptr<Ray>> RayTracer::generateRays(std::shared_ptr<Scene> scene, std::shared_ptr<Pixel> pixel)
{
	std::vector<std::shared_ptr<Ray>> rays;
	glm::vec3 direction = glm::normalize(pixel->m_pos - scene->m_camera->getPosition());
	rays.push_back(std::make_shared<Ray>(scene->m_camera->getPosition(), direction));

	return rays;
}

//returns the image with the pixel dimensions set
std::shared_ptr<Image> RayTracer::genImagePixels(std::shared_ptr<Scene>& scene, int resW, int resH)
{
	std::vector<std::shared_ptr<Pixel>> pixels;

	float height = 2 * scene->m_camera->getFocalLength() * tan((scene->m_camera->getFOV() / 2.0f) * M_PI / 180.0f);
	float width = scene->m_camera->getAspectRatio() * height;

	float pixelWidth = width / resW;
	float pixelHeight = height / resH;

	glm::vec3 iCenter = glm::vec3(scene->m_camera->getPosition().x, scene->m_camera->getPosition().y, 
		scene->m_camera->getPosition().z - scene->m_camera->getFocalLength());

	for (int y = 0; y < resH; ++y)
	{
		for (int x = 0; x < resW; ++x)
		{
			glm::vec3 pixelPos = {
				(iCenter.x - width / 2) + (pixelWidth / 2) + (x * pixelWidth),
				(iCenter.y + height / 2) - (pixelHeight / 2) - (y * pixelHeight),
				iCenter.z
			};

			auto pixel = std::make_shared<Pixel>();
			pixel->m_pos = pixelPos;
			pixels.push_back(pixel);
		}
	}

	auto image = std::make_shared<Image>(resW, resH, pixels);
	return image;
}
