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
	EXPECT_EQ(0x56, a);
	EXPECT_EQ(0x78, r);
	EXPECT_EQ(0x9A, g);
	EXPECT_EQ(0xBC, b);
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

// const Color operator+(const Color& rhs) const
TEST(ColorTest, OperatorPlus1) {
	// Arrange
	Color color1(0x12345678);
	Color color2(0x12345678);

	// Act
	Color result = color1 + color2;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x24, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x68, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0xAC, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0xF0, b);
}

// const Color operator+(const Color& rhs) const
TEST(ColorTest, OperatorPlus2) {
	// Arrange
	Color color1(0x89ABCDEF);
	Color color2(0x9ABCDEF8);

	// Act
	Color result = color1 + color2;

	// Assert
	// 各色オーバーフローするので、最大値0xFFが設定されること
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0xFF, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0xFF, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0xFF, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0xFF, b);
}

// const Color operator-(const Color& rhs) const
TEST(ColorTest, OperatorMinus1) {
	// Arrange
	Color color1(0x89ABCDEF);
	Color color2(0x12345678);

	// Act
	Color result = color1 - color2;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x77, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x77, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x77, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x77, b);
}

// const Color operator-(const Color& rhs) const
TEST(ColorTest, OperatorMinus2) {
	// Arrange
	Color color1(0x12345678);
	Color color2(0xFFFFFFFF);

	// Act
	Color result = color1 - color2;

	// Assert
	// 各色アンダーフローするので、最小値0x00が設定されること
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x00, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x00, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x00, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x00, b);
}
