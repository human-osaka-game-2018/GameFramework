#include "CustomVertex.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSION_11
	#elif defined DIRECT_X_VERSOIN_9
	CustomVertices::CustomVertices()
	{

	}

	CustomVertices::CustomVertices(D3DXVECTOR3& center, RectSize& size, Color& color, TextureUVs& textureUVs)
	{
		Reset(center, size, color, textureUVs);
	}

	CustomVertices::~CustomVertices()
	{

	}

	void CustomVertices::Reset(D3DXVECTOR3& center, RectSize& size, Color& color, TextureUVs& textureUVs)
	{
		const std::vector<D3DXVECTOR2>* pTextureUVs = textureUVs.Get();

		for (auto& vertex : m_vertices)
		{
			int index = static_cast<int>(&vertex - &m_vertices[0]);

			vertex.m_pos = center;
			vertex.m_pos.x += size.m_width  * 0.5f * ((TextureUVs::IsRightSide(index)) ? +1.0f : -1.0f);
			vertex.m_pos.y += size.m_height * 0.5f * ((TextureUVs::IsUnderSide(index)) ? +1.0f : -1.0f);
			vertex.m_aRGB = color.GetColorCode();
			vertex.m_texUV = (*pTextureUVs)[index];
		}
	}

	void CustomVertices::RotateXYZ(Degree& x, Degree& y, Degree& z)
	{
		//回転軸が中心からどのくらい離れているかこの関数では離れていない
		D3DXVECTOR3 relativeRotateCenter(0.0f, 0.0f, 0.0f);

		RotateX(x, relativeRotateCenter);

		RotateY(y, relativeRotateCenter);

		RotateZ(z, relativeRotateCenter);
	}

	void CustomVertices::RotateX(Degree deg, const D3DXVECTOR3& relativeRotateCenter)
	{
		if (deg.Normalized() == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationX(&rotate, D3DXToRadian(deg.Normalized()));
		Rotate(
			relativeRotateCenter,
			rotate);
	}

	void CustomVertices::RotateY(Degree deg, const D3DXVECTOR3& relativeRotateCenter)
	{
		if (deg.Normalized() == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationY(&rotate, D3DXToRadian(deg.Normalized()));
		Rotate(
			relativeRotateCenter,
			rotate);
	}

	void CustomVertices::RotateZ(Degree deg, const D3DXVECTOR3& relativeRotateCenter)
	{
		if (deg.Normalized() == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationZ(&rotate, D3DXToRadian(deg.Normalized()));
		Rotate(
			relativeRotateCenter,
			rotate);
	}

	void CustomVertices::Rotate(const D3DXVECTOR3& relativeRotateCenter, const D3DXMATRIX& rotate)
	{
		//対角線によってすでに回転が行われている矩形の中心も割り出せる
		D3DXVECTOR3 rectCenter((m_vertices[0].m_pos + m_vertices[2].m_pos) * 0.5f);

		//回転の中心は必ずしも矩形の中心ではないので
		D3DXVECTOR3 verticesRectCenterToOrigin[RECT_VERTICES_NUM];
		for (int i = 0; i < RECT_VERTICES_NUM; ++i)
		{
			verticesRectCenterToOrigin[i] = m_vertices[i].m_pos - rectCenter;
		};

		//回転後元の位置に戻すため
		D3DXVECTOR3 verticesRotateCenterToOrigin[RECT_VERTICES_NUM];
		for (int i = 0; i < RECT_VERTICES_NUM; ++i)
		{
			verticesRotateCenterToOrigin[i] = verticesRectCenterToOrigin[i] - relativeRotateCenter;
		};

		for (int i = 0; i < RECT_VERTICES_NUM; ++i)
		{
			D3DXVec3TransformCoord(
				&m_vertices[i].m_pos,
				&verticesRotateCenterToOrigin[i],
				&rotate);

			//元の位置に戻す
			D3DXVec3Add(
				&m_vertices[i].m_pos,
				&m_vertices[i].m_pos,
				&rectCenter);

			D3DXVec3Add(
				&m_vertices[i].m_pos,
				&m_vertices[i].m_pos,
				&relativeRotateCenter);
		}
	}

	#else
	#error "DirectXのバージョンを定義してください"
	#endif
}
