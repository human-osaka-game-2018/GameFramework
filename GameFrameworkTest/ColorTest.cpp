#include "pch.h"

#include "Color.h"

using namespace gameframework;
using COMPONENTS = Color::COMPONENTS;

// Color()
TEST(ColorTest, Ctor0) {
	// Arrange
	// Act
	Color color;

	// Assert
	// GetColorCode()は正常動作する前提
	DWORD ret = color.GetColorCode();
	ASSERT_EQ(0xFFFFFFFF, ret);
}

// Color(DWORD colorCode)
TEST(ColorTest, Ctor1) {
	// Act
	Color color(0x12345678);

	// Assert
	// GetColorCode()は正常動作する前提
	DWORD ret = color.GetColorCode();
	ASSERT_EQ(0x12345678, color.GetColorCode());
}

// Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
TEST(ColorTest, Ctor2) {
	// Act
	Color color(0x9A, 0xBC, 0xDE, 0xF0);

	// Assert
	// GetColorCode()は正常動作する前提
	DWORD ret = color.GetColorCode();
	ASSERT_EQ(0x9ABCDEF0, ret);
}

// DWORD GetColorCode() const
TEST(ColorTest, GetColorCode) {
	// Arrange
	Color color(0x56789ABC);

	// Act
	DWORD ret = color.GetColorCode();

	// Assert
	ASSERT_EQ(0x56789ABC, ret);
}

// BYTE& operator[](COMPONENTS colorComponent)
TEST(ColorTest, OperatorIndexer1) {
	// Arrange
	Color color(0x56789ABC);

	// Act
	BYTE a = color[COMPONENTS::ALPHA];
	BYTE r = color[COMPONENTS::RED];
	BYTE g = color[COMPONENTS::GREEN];
	BYTE b = color[COMPONENTS::BLUE];

	// Assert
	ASSERT_EQ(0x56, a);
	ASSERT_EQ(0x78, r);
	ASSERT_EQ(0x9A, g);
	ASSERT_EQ(0xBC, b);
}

// BYTE& operator[](COMPONENTS colorComponent)
// 異常系
TEST(ColorTest, OperatorIndexer2) {
	// Arrange
	Color color(0x56789ABC);

	// Act
	BYTE ret = color[static_cast<COMPONENTS>(4)];

	// Assert
	ASSERT_EQ(0x00, ret);
}
