#include "Flash.h"

namespace gameframework
{
	Flash::Flash(int flashFrameMax, BYTE alphaMin, BYTE alphaMax) 
		:m_flashFrameMax(flashFrameMax), m_alphaMin(alphaMin), m_alphaMax(alphaMax)
	{

	}

	Flash::~Flash()
	{

	}

	void Flash::Impart(Vertices* pVertices)
	{
		pVertices->Flash(m_flashFrameMax, m_alphaMin, m_alphaMax);
	}
}
