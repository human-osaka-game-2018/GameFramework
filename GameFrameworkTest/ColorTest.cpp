#include "pch.h"

#include "Color.h"

using namespace gameframework;
using COMPONENTS = Color::COMPONENTS;

// GetColorCode()、operator[]は正常動作する前提

// Color()
TEST(ColorTest, DefaultCtor) {
	Color color;

	ASSERT_EQ(0xFFFFFFFF, color.GetColorCode());
	ASSERT_EQ(0xFF, color[COMPONENTS::ALPHA]);
	ASSERT_EQ(0xFF, color[COMPONENTS::RED]);
	ASSERT_EQ(0xFF, color[COMPONENTS::GREEN]);
	ASSERT_EQ(0xFF, color[COMPONENTS::BLUE]);
}

// Color(DWORD colorCode)
TEST(ColorTest, Ctor1) {
	Color color(0x12345678);

	ASSERT_EQ(0x12345678, color.GetColorCode());
	ASSERT_EQ(0x12, color[COMPONENTS::ALPHA]);
	ASSERT_EQ(0x34, color[COMPONENTS::RED]);
	ASSERT_EQ(0x56, color[COMPONENTS::GREEN]);
	ASSERT_EQ(0x78, color[COMPONENTS::BLUE]);
}

// Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
TEST(ColorTest, Ctor2) {
	Color color(0x9A, 0xBC, 0xDE, 0xAA);

	ASSERT_EQ(0x9ABCDEFF, color.GetColorCode());
	ASSERT_EQ(0x9A, color[COMPONENTS::ALPHA]);
	ASSERT_EQ(0xBC, color[COMPONENTS::RED]);
	ASSERT_EQ(0xDE, color[COMPONENTS::GREEN]);
	ASSERT_EQ(0xAA, color[COMPONENTS::BLUE]);
}
