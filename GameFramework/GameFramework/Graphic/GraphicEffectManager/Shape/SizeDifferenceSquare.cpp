#include "SizeDifferenceSquare.h"

namespace gameframework
{
	SizeDifferenceSquare::SizeDifferenceSquare(float sideSize, float differenceSize)
	{
		std::uniform_real_distribution<FLOAT> sizeRand(sideSize, sideSize + differenceSize);

		m_sideSize = sizeRand(m_randEngine);
	}

	SizeDifferenceSquare::~SizeDifferenceSquare()
	{

	}

	void SizeDifferenceSquare::ShapeVertices(Vertices* pVertices)
	{
		pVertices->GetSize() = { m_sideSize, m_sideSize };
	}
}
