#include "Shape.h"

namespace gameframework
{
	Shape::~Shape()
	{

	}

	Shape::Shape()
	{
		std::random_device seed;
		m_randEngine.seed(seed());
	}
}
