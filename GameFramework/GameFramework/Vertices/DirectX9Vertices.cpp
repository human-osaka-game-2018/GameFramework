#include "DirectX9Vertices.h"

namespace gameframework
{
	#ifdef DIRECT_X_VERSOIN_9

	void DirectX9Vertices::Normalize()
	{
		const std::vector<D3DXVECTOR2>* pTextureUVs = m_textureUVs.Get();

		int index = 0;
		for (auto& vertex : m_vertices)
		{
			vertex.m_pos = m_center;
			vertex.m_pos.x += m_halfScale.m_width  * ((TextureUVs::IsRightSide(index)) ? +1.0f : -1.0f);
			vertex.m_pos.y += m_halfScale.m_height * ((TextureUVs::IsUnderSide(index)) ? +1.0f : -1.0f);
			vertex.m_aRGB = m_color.GetColorCode();
			vertex.m_texUV = (*pTextureUVs)[index];

			++index;
		}

		RotateXYZ();
	}

	void DirectX9Vertices::RotateXYZ()
	{
		//回転軸が中心からどのくらい離れているかこの関数では離れていない
		D3DXVECTOR3 relativeRotateCenter(0.0f, 0.0f, 0.0f);

		RotateX(
			m_vertices,
			m_rotationX_deg.Normalized(),
			relativeRotateCenter);

		RotateY(
			m_vertices,
			m_rotationY_deg.Normalized(),
			relativeRotateCenter);

		RotateZ(
			m_vertices,
			m_rotationZ_deg.Normalized(),
			relativeRotateCenter);
	}

	void DirectX9Vertices::RotateX(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		if (deg == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationX(&rotate, D3DXToRadian(deg));
		Rotate(
			pCustomVertices,
			relativeRotateCenter,
			rotate);
	}

	void DirectX9Vertices::RotateY(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		if (deg == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationY(&rotate, D3DXToRadian(deg));
		Rotate(
			pCustomVertices,
			relativeRotateCenter,
			rotate);
	}

	void DirectX9Vertices::RotateZ(CustomVertex* pCustomVertices, float deg, const D3DXVECTOR3& relativeRotateCenter) const
	{
		if (deg == 0.0f) return;

		D3DXMATRIX rotate;
		D3DXMatrixRotationZ(&rotate, D3DXToRadian(deg));
		Rotate(
			pCustomVertices,
			relativeRotateCenter,
			rotate);
	}

	void DirectX9Vertices::Rotate(CustomVertex* pCustomVertices, const D3DXVECTOR3& relativeRotateCenter, const D3DXMATRIX& rRotate) const
	{
		//対角線によってすでに回転が行われている矩形の中心も割り出せる
		D3DXVECTOR3 rectCenter((pCustomVertices[0].m_pos + pCustomVertices[2].m_pos) * 0.5f);

		//回転の中心は必ずしも矩形の中心ではないので
		D3DXVECTOR3 verticesRectCenterToOrigin[CustomVertex::RECT_VERTICES_NUM];
		for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
		{
			verticesRectCenterToOrigin[i] = pCustomVertices[i].m_pos - rectCenter;
		};

		//回転後元の位置に戻すため
		D3DXVECTOR3 verticesRotateCenterToOrigin[CustomVertex::RECT_VERTICES_NUM];
		for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
		{
			verticesRotateCenterToOrigin[i] = verticesRectCenterToOrigin[i] - relativeRotateCenter;
		};

		for (int i = 0; i < CustomVertex::RECT_VERTICES_NUM; ++i)
		{
			D3DXVec3TransformCoord(
				&pCustomVertices[i].m_pos,
				&verticesRotateCenterToOrigin[i],
				&rRotate);

			//元の位置に戻す
			D3DXVec3Add(
				&pCustomVertices[i].m_pos,
				&pCustomVertices[i].m_pos,
				&rectCenter);

			D3DXVec3Add(
				&pCustomVertices[i].m_pos,
				&pCustomVertices[i].m_pos,
				&relativeRotateCenter);
		}
	}

	void DirectX9Vertices::Render(const LPTEXTURE pTexture)
	{
		m_pDirectXGraphicDevice->SetFVF(
			D3DFVF_XYZRHW |
			D3DFVF_DIFFUSE |
			D3DFVF_TEX1);

		m_pDirectXGraphicDevice->SetTexture(0, pTexture);

		m_pDirectXGraphicDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLEFAN,
			2,
			m_vertices,
			sizeof(CustomVertex));
	}

	#endif //DIRECT_X_VERSOIN_9
}
