#include "Color.h"

#include <vector>
#include <unordered_map>
#include <functional>

#include <d3dx9.h>

namespace {
	int Add(BYTE src, BYTE arg) { return src + arg; }
	int Minus(BYTE src, BYTE arg) { return src - arg; }
	float Multiply(BYTE src, float arg) { return src * arg; }
	int Divide(BYTE src, int arg) { return src / arg; }
	int Average(BYTE arg1, BYTE arg2) { return (arg1 + arg2) / 2; }
}

namespace gameframework {
	class Color::Impl {
	public :
		Impl() {
			m_components[COMPONENTS::ALPHA] = 0xFF;
			m_components[COMPONENTS::RED] = 0xFF;
			m_components[COMPONENTS::GREEN] = 0xFF;
			m_components[COMPONENTS::BLUE] = 0xFF;
		}

		Impl(DWORD colorCode) {
			ParseColorCode(colorCode);
		}

		Impl(BYTE alpha, BYTE red, BYTE green, BYTE blue) {
			m_components[COMPONENTS::ALPHA] = alpha;
			m_components[COMPONENTS::RED] = red;
			m_components[COMPONENTS::GREEN] = green;
			m_components[COMPONENTS::BLUE] = blue;
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
		BYTE Normalize(int componentValue) const {
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
		BYTE Normalize(float componentValue) const {
			return Normalize(static_cast<int>(componentValue));
		}

		/// <summary>
		/// カラーコードをparseしARGBに分解する
		/// </summary>
		/// <param name="colorCode">カラーコード</param>
		void ParseColorCode(DWORD colorCode) {
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
				m_components[component] = (colorCode >> shiftNum) & 0xFF;
			}
		}

		DWORD GetColorCode() {
			return D3DCOLOR_ARGB(
				m_components[COMPONENTS::ALPHA],
				m_components[COMPONENTS::RED],
				m_components[COMPONENTS::GREEN],
				m_components[COMPONENTS::BLUE]);
		}

		BYTE& GetComponentValue(COMPONENTS component) { return m_components[component]; }

		template<class T>
		void Calculate(T func, const Color& arg) {
			for (auto& src : m_components) {
				src.second = Normalize(func(src.second, arg[src.first]));
			}
		}

		template<class T>
		void Calculate(T func, float arg) {
			for (auto& src : m_components) {
				src.second = Normalize(func(src.second, arg));
			}
		}

		template<class T>
		void Calculate(T func, int arg) {
			for (auto& src : m_components) {
				src.second = Normalize(func(src.second, arg));
			}
		}

		template<class T>
		void Calculate(T func, DWORD arg) {
			Calculate(func, Color(arg));
		}

	private:
		std::unordered_map<COMPONENTS, BYTE> m_components;
	};

	//-----------------------------------------------------------------
	// Constructors
	//-----------------------------------------------------------------
	Color::Color()
		:m_pImpl(new Impl())
	{
	}

	Color::Color(DWORD colorCode)
		:m_pImpl(new Impl(colorCode))
	{
	}

	Color::Color(BYTE alpha, BYTE red, BYTE green, BYTE blue)
		:m_pImpl(new Impl(alpha, red, green, blue))
	{
	}

	Color::Color(const Color& rhs)
		:m_pImpl(new Impl(rhs.GetColorCode()))
	{
	}

	//-----------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------
	Color::~Color()
	{
	}

	//-----------------------------------------------------------------
	// Public operators
	//-----------------------------------------------------------------
	Color& Color::operator=(const Color& rhs)
	{
		m_pImpl->ParseColorCode(rhs.GetColorCode());
		return *this;
	}

	BYTE& Color::operator[](COMPONENTS colorComponent)
	{
		return m_pImpl->GetComponentValue(colorComponent);
	}

	BYTE Color::operator[](COMPONENTS colorComponent) const
	{
		return m_pImpl->GetComponentValue(colorComponent);
	}

	Color& Color::operator=(DWORD colorCode)
	{
		m_pImpl->ParseColorCode(colorCode);
		return *this;
	}

	Color& Color::operator+=(const Color& rhs)
	{
		m_pImpl->Calculate(Add, rhs);
		return *this;
	}

	Color& Color::operator+=(DWORD rhs)
	{
		m_pImpl->Calculate(Add, rhs);
		return *this;
	}

	Color& Color::operator-=(const Color& rhs)
	{
		m_pImpl->Calculate(Minus, rhs);
		return *this;
	}

	Color& Color::operator-=(DWORD rhs)
	{
		m_pImpl->Calculate(Minus, rhs);
		return *this;
	}

	Color& Color::operator*=(float rhs)
	{
		m_pImpl->Calculate(Multiply, rhs);
		return *this;
	}

	const Color Color::operator/(int rhs) const
	{
		return Color(*this) /= rhs;
	}

	Color& Color::operator/=(int rhs)
	{
		m_pImpl->Calculate(Divide, rhs);
		return *this;
	}

	//-----------------------------------------------------------------
	// Public methods
	//-----------------------------------------------------------------
	DWORD Color::GetColorCode() const
	{
		return m_pImpl->GetColorCode();
	}

	DWORD Color::GetAverageColorCode(DWORD colorCode) const
	{
		Color color(colorCode);
		return GetAverage(color).GetColorCode();
	}

	Color Color::GetAverage(const Color& color) const
	{
		Color ret(*this);
		ret.m_pImpl->Calculate(Average, color);
		return ret;
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
