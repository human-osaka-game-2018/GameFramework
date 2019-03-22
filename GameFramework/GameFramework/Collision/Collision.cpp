#include "Collision.h"

#include <d3dx9.h>

namespace gameframework
{
	namespace collision
	{
		bool IsInner(SideVectors& sideVecs, VectorsVertexToPos& vecsVToP)
		{
			RectDegrees rectDegrees;
			vecsVToP.GetDegrees(&rectDegrees, static_cast<RectVectors*>(&sideVecs));

			//4辺全てから見て点が右側にあるということはその点が矩形に内包されているということになる
			return (rectDegrees >= Degree(0));
		};

		bool IsInner(Vertices& baseVertices, Vertices& vertices)
		{
			SideVectors sideVecs(baseVertices);

			CustomVertex* pCustomVertices = vertices.GetCustomVertex().Get();

			for (int i = 0; CustomVertices::RECT_VERTICES_NUM < 4; ++i)
			{
				VectorsVertexToPos vecsVToP(baseVertices, pCustomVertices[i].m_pos);

				if (IsInner(sideVecs, vecsVToP)) return true;
			}

			//どの頂点も中になかった
			return false;
		};

		bool Collides(Vertices& rectA, Vertices& rectB)
		{
			if (IsInner(rectA, rectB) || IsInner(rectB, rectA))
			{
				return true;
			}

			return false;
		}

		bool IsInner(Vertices& rect, D3DXVECTOR3& pos)
		{
			SideVectors sideVecs(rect);

			VectorsVertexToPos vecsVToP(rect, pos);

			return IsInner(sideVecs, vecsVToP);
		}

		bool CollidesCircles(Vertices& circleA, Vertices& circleB)
		{
			D3DXVECTOR3 vecCenterToCenter = circleA.GetCenter() - circleB.GetCenter();

			if (D3DXVec3Length(&vecCenterToCenter) >
				(circleA.GetSizeForRender().m_width + circleB.GetSizeForRender().m_width) * 0.5f)
			{
				return false;
			}

			return true;
		}

		bool Collides(Vertices& circle, D3DXVECTOR3& Pos)
		{
			D3DXVECTOR3 vecPosToCenter = circle.GetCenter() - Pos;

			if (D3DXVec3Length(&vecPosToCenter) >
				circle.GetSizeForRender().m_width * 0.5f)
			{
				return false;
			}

			return true;
		}
	}
}
