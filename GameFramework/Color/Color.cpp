#include "Color.h"

namespace gameframework {
	//-----------------------------------------------------------------
	// Constructors
	//-----------------------------------------------------------------
	Color::Color()
	{
		m_components[COMPONENTS::ALPHA] = 0xFF;
		m_components[COMPONENTS::RED] = 0xFF;
		m_components[COMPONENTS::GREEN] = 0xFF;
		m_components[COMPONENTS::BLUE] = 0xFF;
	}

	Color::Color(DWORD colorCode)
	{
		ParseColorCode(colorCode, &m_components);
	}

	Color::Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
	{
		m_components[COMPONENTS::ALPHA] = alpha;
		m_components[COMPONENTS::RED] = red;
		m_components[COMPONENTS::GREEN] = green;
		m_components[COMPONENTS::BLUE] = blue;
	}

	//-----------------------------------------------------------------
	// Public operators
	//-----------------------------------------------------------------
	BYTE& Color::operator[](COMPONENTS colorComponent)
	{
		return m_components[colorComponent];
	}

	BYTE Color::operator[](COMPONENTS colorComponent) const
	{
		// constメンバ関数なのでstd::map::operator[]は使えない
		// 代わりにstd::map::at()を使う
		return m_components.at(colorComponent);
	}

	Color& Color::operator=(DWORD colorCode)
	{
		ParseColorCode(colorCode, &m_components);
		return *this;
	}

	Color& Color::operator+=(const Color& rhs)
	{
		for (auto& component : m_components) {
			component.second = Normalize(component.second + rhs[component.first]);
		}

		return *this;
	}

	Color& Color::operator+=(DWORD rhs)
	{
		AddColorCode(rhs);
		return *this;
	}

	Color& Color::operator-=(const Color& rhs)
	{
		for (auto& component : m_components) {
			component.second = Normalize(component.second - rhs[component.first]);
		}

		return *this;
	}

	Color& Color::operator-=(DWORD rhs)
	{
		AddColorCode(rhs, false);
		return *this;
	}

	Color& Color::operator*=(float rhs)
	{
		for (auto& component : m_components) {
			component.second = Normalize(component.second * rhs);
		}

		return *this;
	}

	const Color Color::operator/(int rhs) const
	{
		return Color(*this) /= rhs;
	}

	Color& Color::operator/=(int rhs)
	{
		for (auto& component : m_components) {
			component.second = Normalize(component.second / rhs);
		}

		return *this;
	}

	//-----------------------------------------------------------------
	// Public methods
	//-----------------------------------------------------------------
	DWORD Color::GetColorCode() const
	{
		return D3DCOLOR_ARGB(
			m_components.at(COMPONENTS::ALPHA),
			m_components.at(COMPONENTS::RED),
			m_components.at(COMPONENTS::GREEN),
			m_components.at(COMPONENTS::BLUE));
	}

	DWORD Color::GetAverageColorCode(DWORD colorCode) const
	{
		Color color(colorCode);
		return GetAverage(color).GetColorCode();
	}

	Color Color::GetAverage(const Color& color) const
	{
		Color average;
		for (auto& component : m_components) {
			COMPONENTS argb = component.first;
			average[argb] = (m_components.at(argb) + color[argb]) / 2;
		}

		return average;
	}

	//-----------------------------------------------------------------
	// Private methods
	//-----------------------------------------------------------------
	/// <summary>
	/// 各色(int)の値を0x00～0xFFに正規化する
	/// </summary>
	/// <param name="componentValue">各色の値</param>
	/// <returns>
	/// <para>・cmponentValue ＜ 0x00の場合は0x00を返す</para>
	/// <para>・0x00 ≦ componentValue ≦ 0xFFの場合はcomponentValueをそのまま返す</para>
	/// <para>・0xFF ＜ componentValue 場合は0xFFを返す</para>
	/// </returns>
	BYTE Color::Normalize(int componentValue) const
	{
		return static_cast<BYTE>(max(min(componentValue, 255), 0));
	}

	/// <summary>
	/// 各色(float)の値を0x00～0xFFに正規化する
	/// </summary>
	/// <param name="componentValue">各色の値</param>
	/// <returns>
	/// <para>・cmponentValue ＜ 0x00の場合は0x00を返す</para>
	/// <para>・0x00 ≦ componentValue ≦ 0xFFの場合はcomponentValueをそのまま返す</para>
	/// <para>・0xFF ＜ componentValue 場合は0xFFを返す</para>
	/// </returns>
	BYTE Color::Normalize(float componentValue) const
	{
		return Normalize(static_cast<int>(componentValue));
	}

	/// <summary>
	/// カラーコードをparseしARGBに分解する
	/// </summary>
	/// <param name="colorCode">カラーコード</param>
	/// <param name="pMap">解析結果を詰めるmap</param>
	void Color::ParseColorCode(DWORD colorCode, std::map<COMPONENTS, BYTE>* pMap)
	{
		const std::vector<COMPONENTS> components =
		{
			COMPONENTS::BLUE,
			COMPONENTS::GREEN,
			COMPONENTS::RED,
			COMPONENTS::ALPHA
		};

		for (auto& component : components) {
			int index = static_cast<int>(&component - &components[0]);
			int shiftNum = CHAR_BIT * index;
			(*pMap)[component] = (colorCode >> shiftNum) & 0xFF;
		}
	}

	/// <summary>
	/// カラーコードを加える
	/// </summary>
	/// <param name="colorCode">カラーコード</param>
	/// <param name="isPositive">true:加算、false:減算</param>
	void Color::AddColorCode(DWORD colorCode, bool isPositive)
	{
		std::map<COMPONENTS, BYTE> components;
		ParseColorCode(colorCode, &components);

		for (auto& component : m_components) {
			COMPONENTS color = component.first;
			int value = components[color] * (isPositive ? 1 : -1);
			m_components[color] = Normalize(m_components[color] + value);
		}
	}

	//-----------------------------------------------------------------
	// Global operators
	//-----------------------------------------------------------------
	Color operator+(const Color& lhs, const Color& rhs)
	{
		return Color(lhs) += rhs;
	}

	Color operator+(const Color& lhs, DWORD rhs)
	{
		return Color(lhs) += rhs;
	}

	Color operator+(DWORD lhs, const Color& rhs)
	{
		return Color(lhs) += rhs;
	}

	Color operator-(const Color& lhs, const Color& rhs)
	{
		return Color(lhs) -= rhs;
	}

	Color operator-(const Color& lhs, DWORD rhs)
	{
		return Color(lhs) -= rhs;
	}

	Color operator-(DWORD lhs, const Color& rhs)
	{
		return Color(lhs) -= rhs;
	}

	Color operator*(const Color& lhs, float rhs)
	{
		return Color(lhs) *= rhs;
	}

	Color operator*(float lhs, const Color& rhs)
	{
		return Color(rhs) *= lhs;
	}
}

