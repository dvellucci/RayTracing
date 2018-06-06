#include "FileReader.h"

FileReader::FileReader(std::string filePath)
{
	std::ifstream input_file_stream(std::string(filePath), std::ios::in);

	if (input_file_stream.is_open())
	{
		std::string fileLine = "";
		while (getline(input_file_stream, fileLine))
		{
			m_fileInputLines.push_back(fileLine);
		}
	}
}

FileReader::~FileReader()
{
}

std::shared_ptr<Scene> FileReader::setObjectData()
{
	auto scene = std::make_shared<Scene>();
	std::string currLine = "";
	for (int i = 0; i < m_fileInputLines.size(); i++)
	{
		if (m_fileInputLines[i] == "camera")
		{
			auto camera = std::make_shared<Camera>();

			//next line - get camera position
			i++;
			glm::vec3 pos;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &pos.x, &pos.y, &pos.z);
			camera->setPosition(pos);

			//next line - get camera fov
			i++;
			float fov;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &fov);
			camera->setFOV(fov);

			//next line - get focal length
			i++;
			float fl;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &fl);
			camera->setFocalLength(fl);

			//next line - get aspect ratio
			i++;
			float ar;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &ar);

			camera->setAspectRatio(ar);

			//make the camera in the scene
			scene->m_camera = camera;
		}
		else if (m_fileInputLines[i] == "sphere")
		{
			auto sphere = std::make_shared<Sphere>();

			//set the sphere's center
			i++;
			glm::vec3 center;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &center.x, &center.y, &center.z);
			sphere->setCenter(center);

			//set the sphere's radius
			i++;
			float radius = 0.0f;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &radius);
			sphere->setRadius(radius);

			//set ambience
			i++;
			glm::vec3 amb;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &amb.x, &amb.y, &amb.z);
			sphere->setAmbience(amb);

			//set diffuse
			i++;
			glm::vec3 diffuse;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &diffuse.x, &diffuse.y, &diffuse.z);
			sphere->setDiffuse(diffuse);

			//set specular
			i++;
			glm::vec3 spec;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &spec.x, &spec.y, &spec.z);
			sphere->setSpecular(spec);

			//set shininess
			i++;
			float shiny;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &shiny);
			sphere->setShiny(shiny);

			//add the new sphere to the scene
			scene->m_spheres.push_back(sphere);
		}
		else if (m_fileInputLines[i] == "plane")
		{
			auto plane = std::make_shared<Plane>();

			//set the normal
			i++;
			glm::vec3 n;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &n.x, &n.y, &n.z);
			plane->setNormal(n);

			//set plane pos
			i++;
			glm::vec3 pos;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &pos.x, &pos.y, &pos.z);
			plane->setPoint(pos);

			//set ambience
			i++;
			glm::vec3 amb;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &amb.x, &amb.y, &amb.z);
			plane->setAmbience(amb);

			//set diffuse
			i++;
			glm::vec3 diff;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &diff.x, &diff.y, &diff.z);
			plane->setDiffuse(diff);

			//set specular
			i++;
			glm::vec3 spec;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &spec.x, &spec.y, &spec.z);
			plane->setSpecular(spec);

			//set shininess
			i++;
			float shiny;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &shiny);
			plane->setShiny(shiny);

			scene->m_planes.push_back(plane);
		}
		else if (m_fileInputLines[i] == "light")
		{
			auto light = std::make_shared<Light>();

			i++;
			glm::vec3 lightPos;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &lightPos.x, &lightPos.y, &lightPos.z);
			light->setPosition(lightPos);

			i++;
			glm::vec3 lightColor;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f %f %f", &lightColor.x, &lightColor.y, &lightColor.z);
			light->setColor(lightColor);

			scene->m_lights.push_back(light);
		}
	}

	return scene;
}
