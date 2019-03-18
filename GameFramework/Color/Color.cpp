#include "Color.h"

namespace gameframework {
	//-----------------------------------------------------------------
	// Constructors
	//-----------------------------------------------------------------
	Color::Color() {}

	Color::Color(DWORD colorCode)
	{
		(*this) = colorCode;
	}

	Color::Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
		:m_alpha(alpha), m_red(red), m_green(green), m_blue(blue)
	{}

	//-----------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------
	Color::~Color() {}

	//-----------------------------------------------------------------
	// Public operators
	//-----------------------------------------------------------------
	BYTE& Color::operator[](COMPONENTS colorComponent)
	{
		switch (colorComponent)
		{
		case COMPONENTS::ALPHA:
			return m_alpha;

		case COMPONENTS::RED:
			return m_red;

		case COMPONENTS::GREEN:
			return m_green;

		case COMPONENTS::BLUE:
			return m_blue;

		default:
		{
			//ここに来ることは基本ない
			static BYTE errorReturnVal = 0x00;
			return errorReturnVal;
		}
		}
	}

	Color& Color::operator=(DWORD colorCode)
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
			(*this)[component] = (colorCode >> shiftNum) & 0xFF;
		}

		return *this;
	}

	const Color Color::operator+(const Color& rhs) const
	{
		return Color(
			Normalize(m_alpha + rhs.m_alpha),
			Normalize(m_red + rhs.m_red),
			Normalize(m_green + rhs.m_green),
			Normalize(m_blue + rhs.m_blue)
		);
	}

	const Color Color::operator+(DWORD rhs) const
	{
		return Color((*this) + Color(rhs));
	}

	const Color Color::operator-(const Color& rhs) const
	{
		return Color(
			Normalize(m_alpha - rhs.m_alpha),
			Normalize(m_red - rhs.m_red),
			Normalize(m_green - rhs.m_green),
			Normalize(m_blue - rhs.m_blue)
		);
	}

	const Color Color::operator-(DWORD rhs) const
	{
		return Color((*this) - Color(rhs));
	}

	const Color Color::operator+=(const Color& rhs)
	{
		(*this) = (*this) + rhs;

		return *this;
	}

	const Color Color::operator+=(DWORD rhs)
	{
		(*this) = (*this) + rhs;

		return *this;
	}

	const Color Color::operator-=(const Color& rhs)
	{
		(*this) = (*this) - rhs;

		return *this;
	}

	const Color Color::operator-=(DWORD rhs)
	{
		(*this) = (*this) - rhs;

		return *this;
	}

	const Color Color::operator*(float rhs) const
	{
		return Color(
			Normalize(m_alpha * rhs),
			Normalize(m_red   * rhs),
			Normalize(m_green * rhs),
			Normalize(m_blue  * rhs)
		);
	}
	Color& Color::operator*=(float rhs)
	{
		(*this) = (*this) * rhs;

		return *this;
	}

	const Color Color::operator/(int rhs) const
	{
		return Color(
			Normalize(m_alpha / rhs),
			Normalize(m_red / rhs),
			Normalize(m_green / rhs),
			Normalize(m_blue / rhs)
		);
	}

	Color& Color::operator/=(int rhs)
	{
		(*this) = (*this) / rhs;

		return *this;
	}

	//-----------------------------------------------------------------
	// Public methods
	//-----------------------------------------------------------------
	DWORD Color::GetAverageColorCode(DWORD colorCode) const
	{
		Color inColor(colorCode);

		return GetAverage(inColor).GetColorCode();
	}

	Color Color::GetAverage(const Color & color) const
	{
		Color average(
			(m_alpha + color.m_alpha) / 2,
			(m_red + color.m_red) / 2,
			(m_green + color.m_green) / 2,
			(m_blue + color.m_blue) / 2);

		return average;
	}

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
}

