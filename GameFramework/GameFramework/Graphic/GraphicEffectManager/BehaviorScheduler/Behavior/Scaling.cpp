#include "Scaling.h"

namespace gameframework
{
	Scaling::Scaling(float additionalAmount) :m_additionalAmount(additionalAmount)
	{

	}

	Scaling::~Scaling()
	{

	}

	void Scaling::Impart(Vertices* pVertices)
	{
		pVertices->GetSize() += m_additionalAmount;
		++m_lifeFrame;
	}
}
