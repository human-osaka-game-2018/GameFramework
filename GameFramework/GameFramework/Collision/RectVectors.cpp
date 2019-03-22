#include "RectVectors.h"

namespace gameframework
{
	namespace collision
	{
		RectVectors::~RectVectors()
		{

		}

		void RectVectors::GetDegrees(RectDegrees* pRectDegrees, const RectVectors* pRectVectors)const
		{
			const D3DXVECTOR2* pRECT_VECS = pRectVectors->Get();

			for (auto& vec : m_vectors)
			{
				int index = static_cast<int>(&vec - &m_vectors[0]);

				pRectDegrees->m_degrees[index] = algorithm::D3DXVec2CalcDegree(m_vectors[index], pRECT_VECS[index]);
			}
		}

		RectVectors::RectVectors()
		{

		}
	}
}
