#include "VectorsVertexToPos.h"

namespace gameframework
{
	namespace collision
	{
		VectorsVertexToPos::VectorsVertexToPos(Vertices& vertices, D3DXVECTOR3& pos)
		{
			Create(vertices, pos);
		}

		VectorsVertexToPos::~VectorsVertexToPos()
		{

		}

		void VectorsVertexToPos::Create(Vertices& vertices, D3DXVECTOR3& pos)
		{
			CustomVertices& customVertices = vertices.GetCustomVertex();
			CustomVertex* pCustomVertices  = customVertices.Get();

			for (auto& vecVtoP : m_vectors)
			{
				int index = static_cast<int>(&vecVtoP - &m_vectors[0]);

				//一つ先の頂点とのベクトルを作成
				D3DXVECTOR3 vec3Tmp = pCustomVertices[index].m_pos - pos;

				vecVtoP = { vec3Tmp.x, vec3Tmp.y };
			}
		}
	}
}
