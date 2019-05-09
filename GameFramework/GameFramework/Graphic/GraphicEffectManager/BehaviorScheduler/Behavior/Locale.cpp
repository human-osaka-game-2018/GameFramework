#include "Locale.h"

namespace gameframework
{
	Locale::Locale(const D3DXVECTOR3& pos) :m_pos(pos)
	{

	}

	Locale::~Locale()
	{

	}

	void Locale::Impart(Vertices* pVertices)
	{
		pVertices->SetCenter(m_pos);
	}
}
