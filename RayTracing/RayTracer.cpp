#include "RayTracer.h"

RayTracer::RayTracer() : m_recursionDepth(2.0f)
{
}

RayTracer::~RayTracer()
{
}

//traces only a section of the pixels. Used for multi-threading
void RayTracer::traceChunk(std::vector<std::shared_ptr<Pixel>> pixels, int start, int stride, std::shared_ptr<Scene> scene)
{
	//trace the chunk of pixels specified by the start and count variables
	for (int i = start; i < start + stride; ++i)
	{
		std::shared_ptr<Ray> ray = generateRay(scene, pixels[i]);
		//set the color of the pixels to the color generated by the trace
		pixels[i]->m_color = trace(ray, scene, 0);
	}
}

glm::vec3 RayTracer::trace(std::shared_ptr<Ray> ray, std::shared_ptr<Scene> scene, int depth)
{
	float t_temp;
	float t_value = FLT_MAX;
	glm::vec3 tempNormal, normal;
	std::shared_ptr<Surface> surface;

	//intersect the spheres
	for(int i = 0; i < scene->m_spheres.size(); i++)
	{
		auto sphere = scene->m_spheres[i];
		if (sphere->hit(ray, t_temp, tempNormal))
		{
			if (t_temp < t_value)
			{
				t_value = t_temp;
				normal = tempNormal;
				//save the surface so it can be passed into the light function
				surface = sphere;
			}
		}
	}

	//intersect the planes
	for (int i = 0; i < scene->m_planes.size(); i++)
	{
		auto plane = scene->m_planes[i];
		if (plane->hit(ray, t_temp, tempNormal))
		{
			if (t_temp < t_value)
			{
				t_value = t_temp;
				normal = tempNormal;
				//save the surface so it can be passed into the light function
				surface = plane;
			}
		}
	}

	if (depth > m_recursionDepth || (abs(t_value - FLT_MAX) < FLT_MIN))
		return glm::vec3(0.1f, 0.1f, 0.1f);

	glm::vec3 intersection = ray->getOrigin() + t_value * ray->getDirection();

	//get the reflect ray
	auto reflectRay = getReflectRay(ray->getDirection(), intersection, normal);

	//glm::vec3 color = lightColor(scene, intersection, surface, normal, -ray->getDirection());
	glm::vec3 color = surfaceColor(scene, intersection, surface, normal, -ray->getDirection()) + 0.15f * trace(reflectRay, scene, depth + 1);

	return color;
}

glm::vec3 RayTracer::surfaceColor(std::shared_ptr<Scene> scene, glm::vec3 intersection, std::shared_ptr<Surface> surface,
	glm::vec3 norm, glm::vec3 rayDir)
{		
	glm::vec3 color = surface->getAmbience();
	for (auto light : scene->m_lights)
	{
		float tmin = glm::distance(light->getPosition(), intersection);
		glm::vec3 normal;

		bool shadowed = false;

		//create the shadow ray
		glm::vec3 shadowDir = glm::normalize(light->getPosition() - intersection);
		glm::vec3 origin = intersection + 0.1f * shadowDir;
		auto shadowRay = std::make_shared<Ray>(origin, shadowDir);

		//check for spheres that are shadowed
		for (int i = 0; i < scene->m_spheres.size(); i++) 
		{
			auto sphere = scene->m_spheres[i];
			if (sphere->hit(shadowRay, tmin, normal))
			{
				shadowed = true;
				break;
			}
		}

		//check for planes that are shadowed
		for (int i = 0; i < scene->m_planes.size(); i++)
		{
			auto plane = scene->m_planes[i];
			if (plane->hit(shadowRay, tmin, normal))
			{
				shadowed = true;
				break;
			}
		}

		//calculate phong lighting if something is not shadowed
		if (!shadowed)
		{
			color += calculatePhong(light, shadowRay, surface, norm, rayDir);
		}

	}

	return color;
}

//calculate the phong lighting for each ray intersection
glm::vec3 RayTracer::calculatePhong(std::shared_ptr<Light> light, std::shared_ptr<Ray> ray,
	std::shared_ptr<Surface> surface, glm::vec3 norm, glm::vec3 rayDir)
{
	glm::vec3 lightDirection = ray->getDirection();
	glm::vec3 reflectionVector = 2 * glm::dot(lightDirection, norm) * norm - lightDirection;

	float reflectDot = glm::dot(reflectionVector, rayDir);

	glm::vec3 specular = surface->getSpecular() * pow(glm::max(0.0f, reflectDot), surface->getShiny());
	glm::vec3 diffuse = surface->getDiffuse() * glm::dot(lightDirection, norm);

	glm::vec3 color = light->getColor() * (diffuse + specular);

	return color; 
}

//generates the ray and its direction from each pixel
std::shared_ptr<Ray> RayTracer::generateRay(std::shared_ptr<Scene> scene, std::shared_ptr<Pixel> pixel)
{
	std::vector<std::shared_ptr<Ray>> rays;
	glm::vec3 direction = glm::normalize(pixel->m_pos - scene->m_camera->getPosition());
	rays.push_back(std::make_shared<Ray>(scene->m_camera->getPosition(), direction));

	return std::make_shared<Ray>(scene->m_camera->getPosition(), direction);
}

std::shared_ptr<Ray> RayTracer::getReflectRay(glm::vec3 rayDirection, glm::vec3 intersection, glm::vec3 norm)
{
	//get the reflection ray direction, the origin of the ray and create it
	glm::vec3 reflectDirection = -2 * glm::dot(rayDirection, norm) * norm + (rayDirection);
	//get the origin but add an offset to it so the ray doesn't hit the same object
	//credit for reflect ray origin formula: https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
	glm::vec3 reflectRayOrigin = intersection + 0.1f * reflectDirection;
	auto reflectRay = std::make_shared<Ray>(reflectRayOrigin, reflectDirection);
	return reflectRay;
}

