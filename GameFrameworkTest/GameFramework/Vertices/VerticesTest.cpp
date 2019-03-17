#include "pch.h"

#include "DirectX9Vertices.h"
#include "Window.h"

using namespace gameframework;

namespace {
	class VerticesSpy : public DirectX9Vertices {
	public:
		RectSize GetBaseHalfScale() { return m_baseHalfScale; }
		RectSize GetHalfScale() { return m_halfScale; }
	};

	class VerticesTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
			Window window(_T("VerticesTest"));
			DirectXParam::Create();
			pVertices = new VerticesSpy();
			pVertices->SetHalfScale(RectSize(WIDTH, HEIGHT));
			pVertices->SetCenter(D3DXVECTOR3(100.0f, 50.0f, 25.0f));
		}

		virtual void TearDown() {
			delete pVertices;
		}

		VerticesSpy* pVertices;
		const float WIDTH = 64.0f;
		const float HEIGHT = 96.0f;
	};
}

// Color()
TEST_F(VerticesTest, Ctor0) {
	// Arrange
	int frames = 5;
	float initialScale = 0.5f;
	float finalScale = 2.0f;
	float initialWidth;

	// Act
	for (int i = 0; i < frames; ++i) {
		pVertices->ScalingX(frames, initialScale, finalScale);
		if (i == 0) {
			initialWidth = pVertices->GetBaseHalfScale().m_width;
		}
	}

	float result = pVertices->GetBaseHalfScale().m_width;

	// Assert
	EXPECT_FLOAT_EQ(WIDTH * initialScale, initialWidth);
	EXPECT_FLOAT_EQ(WIDTH * finalScale, result);
}
