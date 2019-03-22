#include "SideVectors.h"

namespace gameframework
{
	namespace collision
	{
		SideVectors::SideVectors(Vertices& vertices)
		{
			Create(vertices);
		}

		SideVectors::~SideVectors()
		{

		}

		void SideVectors::Create(Vertices& vertices)
		{
			CustomVertices& customVertices = vertices.GetCustomVertex();
			CustomVertex* pCustomVertices  = customVertices.Get();

			for (auto& sideVec : m_vectors)
			{
				int index = static_cast<int>(&sideVec - &m_vectors[0]);

				//一つ先の頂点とのベクトルを作成
				D3DXVECTOR3 vec3Tmp = pCustomVertices[(index + 1) % 4].m_pos - pCustomVertices[index].m_pos;

				sideVec = { vec3Tmp.x, vec3Tmp.y };
			}
		}
	}
}
