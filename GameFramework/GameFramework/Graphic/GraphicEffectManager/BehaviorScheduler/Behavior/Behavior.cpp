#include "Behavior.h"

namespace gameframework
{
	Behavior::~Behavior()
	{
		
	}

	Behavior::Behavior()
	{
		std::random_device seed;
		m_randEngine.seed(seed());
	}
}
