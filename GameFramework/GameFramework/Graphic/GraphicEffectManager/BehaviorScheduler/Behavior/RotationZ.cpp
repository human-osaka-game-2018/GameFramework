#include "RotationZ.h"

namespace gameframework
{
	RotationZ::RotationZ(Degree degree) :m_degree(degree)
	{

	}

	RotationZ::~RotationZ()
	{

	}

	void RotationZ::Impart(Vertices* pVertices)
	{
		pVertices->AddRotationZ(m_degree);
	}
}
