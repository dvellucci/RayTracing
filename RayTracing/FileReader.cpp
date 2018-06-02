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
			camera->m_pos = pos;

			//next line - get camera fov
			i++;
			float fov;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &fov);
			camera->m_fov = fov;

			//next line - get focal length
			i++;
			float fl;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &fl);
			camera->m_focalLength = fl;

			//next line - get aspect ratio
			i++;
			float ar;
			sscanf_s(m_fileInputLines[i].c_str(), "%*s %f", &ar);

			if (abs(ar - float(4) / 3) < ASPECT_EPSILON)
			{
				ar = (4 / 3);
			}
			else if (abs(ar - float(16) / 9) < ASPECT_EPSILON)
			{
				ar = (16 / 9);
			}
			else if (abs(ar - float(64) / 27) < ASPECT_EPSILON)
			{
				ar = (64 / 27);
			}

			//make the camera in the scene
			scene->m_camera = camera;
		}
		if (m_fileInputLines[i] == "sphere")
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

			//add the new sphere to the scene
			scene->m_spheres.push_back(sphere);
		}
	}

	return scene;
}
