#include "Collision.h"

#include <d3dx9.h>

namespace gameframework
{
	namespace collision
	{
		void CreateSideVectors(D3DXVECTOR2* pSideVecs, const CustomVertex* pVertices)
		{
			for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
			{
				//一つ先の頂点とのベクトルを作成
				D3DXVECTOR3 vec3Tmp = pVertices[(i + 1) % 4].m_pos - pVertices[i].m_pos;

				pSideVecs[i] = { vec3Tmp.x, vec3Tmp.y };
			}
		};

		void CreateVectorsVertexToPos(D3DXVECTOR2* pVecsVToP, const CustomVertex* pVertices, const D3DXVECTOR3& pos)
		{
			for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
			{
				D3DXVECTOR3 vec3Tmp = pos - pVertices[i].m_pos;

				pVecsVToP[i] = { vec3Tmp.x, vec3Tmp.y };
			}
		};

		bool IsInner(const D3DXVECTOR2* pSideVecs, const D3DXVECTOR2 * pVecsVToP)
		{
			for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
			{
				//角度が正ならば+で帰ってくる
				float degree = algorithm::D3DXVec2CalcDegree(pSideVecs[i], pVecsVToP[i]);

				//負ならば辺の左側に点があるということになるので矩形の中に点は存在していない
				if (degree < 0) return false;
			}

			//4辺全てから見て点が右側にあるということはその点が矩形に内包されているということになる
			return true;
		};

		bool Collides(const CustomVertex* pBaseVertices, const CustomVertex* pVertices)
		{
			D3DXVECTOR2 sideVecs[CustomVertex::RECT_VERTICES_NUM];
			CreateSideVectors(sideVecs, pBaseVertices);

			for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
			{
				D3DXVECTOR2 vecsVToP[CustomVertex::RECT_VERTICES_NUM];
				CreateVectorsVertexToPos(vecsVToP, pBaseVertices, pVertices[i].m_pos);

				if (IsInner(sideVecs, vecsVToP)) return true;
			}

			//どの頂点も中になかった
			return false;
		};

		bool Collides(Vertices& rectA, Vertices& rectB)
		{
			if (Collides(rectA.GetCustomVertex(), rectB.GetCustomVertex()) ||
				Collides(rectB.GetCustomVertex(), rectA.GetCustomVertex()))
			{
				return true;
			}

			return false;
		}

		bool IsInner(Vertices& rect, D3DXVECTOR3& pos)
		{
			D3DXVECTOR2 sideVecs[CustomVertex::RECT_VERTICES_NUM];
			CreateSideVectors(sideVecs, rect.GetCustomVertex());

			D3DXVECTOR2 vecVToP[CustomVertex::RECT_VERTICES_NUM];
			CreateVectorsVertexToPos(vecVToP, rect.GetCustomVertex(), pos);

			return IsInner(sideVecs, vecVToP);
		}

		bool Collides(Vertices& circleA, Vertices& circleB)
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
