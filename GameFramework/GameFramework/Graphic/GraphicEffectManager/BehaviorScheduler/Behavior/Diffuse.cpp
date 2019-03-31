#include "Diffuse.h"

namespace gameframework
{
	Diffuse::Diffuse(float movement, const Degree& min, const Degree& width_deg)
	{
		m_baseMovementVec = { 0.0f, movement };

		std::uniform_real_distribution<FLOAT> degRand(min.Raw(), min.Raw() + width_deg.Raw());

		algorithm::D3DXVec2RotationZ(&m_baseMovementVec, degRand(m_randEngine));
	}

	Diffuse::~Diffuse()
	{

	}

	void Diffuse::Impart(Vertices* pVertices)
	{
		pVertices->GetCenter().x += m_baseMovementVec.x;
		pVertices->GetCenter().y += m_baseMovementVec.y;
	}
}
