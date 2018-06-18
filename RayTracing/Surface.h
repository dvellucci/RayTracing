#pragma once
#ifndef SURFACEH
#define SURFACEH
#include "Ray.h"
#include <memory>

class Surface
{
public:

	Surface();
	~Surface();

	virtual bool hit(std::shared_ptr<Ray> ray, float &t, glm::vec3& norm) = 0;

	//set all the color components for the surfaces
	void setAmbience(glm::vec3 amb) { m_ambColor = amb; }
	void setDiffuse(glm::vec3 diff) { m_diffColor = diff; }
	void setSpecular(glm::vec3 spec) { m_specColor = spec; }
	void setShiny(float shiny) { m_shiny = shiny; }

	glm::vec3 getAmbience() { return m_ambColor; }
	glm::vec3 getDiffuse() { return m_diffColor; }
	glm::vec3 getSpecular() { return m_specColor; }

	float getShiny() { return m_shiny; }

private:

	//light variables
	glm::vec3 m_ambColor;
	glm::vec3 m_diffColor;
	glm::vec3 m_specColor;

	float m_shiny;
};

#endif