#pragma once
#include <vector>
#include <memory>
#include "Pixel.h"

class Image
{
public:
	Image(int width, int height, std::vector <std::shared_ptr<Pixel>> pixels) : m_width(width), 
		m_height(height), m_pixels(pixels) {};
	~Image() {};

	std::vector <std::shared_ptr<Pixel>> m_pixels;

	int m_width, m_height;
private:
};