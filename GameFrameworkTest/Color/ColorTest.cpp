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

// DWORD GetAverageColorCode(DWORD colorCode) const
TEST(ColorTest, GetAverageColorCode) {
	// 確認しようが無いので省略
	SUCCEED();
}

// Color GetAverage(const Color& color) const
TEST(ColorTest, GetAverage) {
	// Arrange
	Color color1(0x11, 0x33, 0x55, 0x77);
	Color color2(0x01, 0x03, 0x05, 0x07);

	// Act
	Color ret = color1.GetAverage(color2);

	// Assert
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(0x09, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(0x1B, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(0x2D, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(0x3F, ret_b);
}

// Color GetAverage(const Color& color) const
TEST(ColorTest, GetAverage2) {
	// Arrange
	Color color1(0xFC, 0xFD, 0xFE, 0xFF);
	Color color2(0xFF, 0xFF, 0xFF, 0xFF);

	// Act
	Color ret = color1.GetAverage(color2);

	// Assert
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(0xFD, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(0xFE, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(0xFE, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(0xFF, ret_b);
}

// BYTE& operator[](COMPONENTS colorComponent)
TEST(ColorTest, OperatorIndexer1) {
	// Arrange
	Color color(0x56, 0x78, 0x9A, 0xBC);

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
	Color color1(0x12, 0x34, 0x56, 0x78);
	Color color2(0x12, 0x34, 0x56, 0x78);

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
	Color color1(0x89, 0xAB, 0xCD, 0xEF);
	Color color2(0x9A, 0xBC, 0xDE, 0xF8);

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

// const Color operator+(DWORD rhs) const
TEST(ColorTest, OperatorPlus3) {
	// Arrange
	Color color(0x12, 0x34, 0x56, 0x78);

	// Act
	Color result = color + 0x01234567;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x13, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x57, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x9B, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0xDF, b);
}

// const Color operator-(const Color& rhs) const
TEST(ColorTest, OperatorMinus1) {
	// Arrange
	Color color1(0x89, 0xAB, 0xCD, 0xEF);
	Color color2(0x12, 0x34, 0x56, 0x78);

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
	Color color1(0x12, 0x34, 0x56, 0x78);
	Color color2(0xFF, 0xFF, 0xFF, 0xFF);

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

// const Color operator-(DWORD rhs) const
TEST(ColorTest, OperatorMinus3) {
	// Arrange
	Color color(0x12, 0x34, 0x56, 0x78);

	// Act
	Color result = color - 0x01234567;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x11, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x11, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x11, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x11, b);
}

// const Color operator+=(const Color& rhs)
TEST(ColorTest, OperatorPlusEq1) {
	// Arrange
	Color lhs(0x12, 0x34, 0x56, 0x78);
	Color rhs(0x12, 0x34, 0x56, 0x78);

	// Act
	Color ret = (lhs += rhs);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x24, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x68, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0xAC, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0xF0, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}

// const Color operator+=(DWORD rhs)
TEST(ColorTest, OperatorPlusEq2) {
	// Arrange
	Color lhs(0x12, 0x34, 0x56, 0x78);

	// Act
	Color ret = (lhs += 0x12345678);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x24, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x68, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0xAC, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0xF0, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}

// const Color operator-=(const Color& rhs)
TEST(ColorTest, OperatorMinusEq1) {
	// Arrange
	Color lhs(0x12, 0x34, 0x56, 0x78);
	Color rhs(0x11, 0x11, 0x11, 0x11);

	// Act
	Color ret = (lhs -= rhs);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x01, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x23, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0x45, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0x67, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}

// const Color operator-=(DWORD rhs)
TEST(ColorTest, OperatorMinusEq2) {
	// Arrange
	Color lhs(0x12, 0x34, 0x56, 0x78);

	// Act
	Color ret = (lhs -= 0x11111111);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x01, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x23, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0x45, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0x67, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}

// const Color operator*(float rhs) const
TEST(ColorTest, OperatorMultiply1) {
	// Arrange
	Color color(0x12, 0x22, 0x32, 0x42);

	// Act
	Color result = color * 2.0f;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x24, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x44, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x64, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x84, b);
}

// const Color operator*(float rhs) const
TEST(ColorTest, OperatorMultiply2) {
	// Arrange
	Color color(0x11, 0x21, 0x31, 0x41);

	// Act
	Color result = color * 2.5;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x2A, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x52, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x7A, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0xA2, b);
}

// const Color operator*(float rhs) const
TEST(ColorTest, OperatorMultiply3) {
	// Arrange
	Color color(0x12, 0x34, 0x56, 0x78);

	// Act
	Color result = color * (-0.5);

	// Assert
	// 全色アンダーフローして0x00になることを確認
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x00, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x00, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x00, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x00, b);
}

// const Color operator*(float rhs) const
TEST(ColorTest, OperatorMultiply4) {
	// Arrange
	Color color(0x12, 0x34, 0x56, 0x78);

	// Act
	Color result = color * 100.0f;

	// Assert
	// 全色オーバーフローして0xFFになることを確認
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0xFF, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0xFF, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0xFF, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0xFF, b);
}

// Color& operator*=(float rhs)
TEST(ColorTest, OperatorMultiplyEq) {
	// Arrange
	Color lhs(0x12, 0x22, 0x32, 0x42);

	// Act
	Color ret = (lhs *= 2.0f);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x24, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x44, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0x64, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0x84, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}

// const Color operator/(int rhs) const
TEST(ColorTest, OperatorDevide1) {
	// Arrange
	Color color(0x02, 0x12, 0x22, 0x32);

	// Act
	Color result = color / 2;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x01, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x09, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x11, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x19, b);
}

// const Color operator/(int rhs) const
TEST(ColorTest, OperatorDevide2) {
	// Arrange
	Color color(0x02, 0x12, 0x22, 0x32);

	// Act
	Color result = color / 16;

	// Assert
	BYTE a = result[COMPONENTS::ALPHA];
	EXPECT_EQ(0x00, a);

	BYTE r = result[COMPONENTS::RED];
	EXPECT_EQ(0x01, r);

	BYTE g = result[COMPONENTS::GREEN];
	EXPECT_EQ(0x02, g);

	BYTE b = result[COMPONENTS::BLUE];
	EXPECT_EQ(0x03, b);
}

// Color& operator/=(int rhs)
TEST(ColorTest, OperatorDevideEQ1) {
	// Arrange
	Color lhs(0x88, 0x42, 0x14, 0xF2);

	// Act
	Color ret = (lhs /= 4);

	// Assert
	// lhsの値が正しく更新されていることを確認
	BYTE lhs_a = lhs[COMPONENTS::ALPHA];
	EXPECT_EQ(0x22, lhs_a);

	BYTE lhs_r = lhs[COMPONENTS::RED];
	EXPECT_EQ(0x10, lhs_r);

	BYTE lhs_g = lhs[COMPONENTS::GREEN];
	EXPECT_EQ(0x05, lhs_g);

	BYTE lhs_b = lhs[COMPONENTS::BLUE];
	EXPECT_EQ(0x3C, lhs_b);

	// 更新されたlhsと同じ値が返却されていることを確認
	BYTE ret_a = ret[COMPONENTS::ALPHA];
	EXPECT_EQ(lhs_a, ret_a);

	BYTE ret_r = ret[COMPONENTS::RED];
	EXPECT_EQ(lhs_r, ret_r);

	BYTE ret_g = ret[COMPONENTS::GREEN];
	EXPECT_EQ(lhs_g, ret_g);

	BYTE ret_b = ret[COMPONENTS::BLUE];
	EXPECT_EQ(lhs_b, ret_b);
}
