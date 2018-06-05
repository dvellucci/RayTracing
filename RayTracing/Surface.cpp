#include "Surface.h"

Surface::Surface()
{
}

Surface::~Surface()
{
}

bool Surface::quadratic(const float & a, const float & b, const float & c, float & x0, float & x1)
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

	//make x0 the smaller value
	if (x0 > x1) std::swap(x0, x1);

	if (x0 < 0) 
	{
		x0 = x1;
		if (x0 < 0) 
			return false;
	}

	return true;
}