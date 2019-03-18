#ifndef COLOR_H
#define COLOR_H

#include <Windows.h>
#include <vector>

#include <d3dx9.h>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	/// <summary>
	/// 色保存するためのクラス
	/// </summary>
	class Color
	{
	public:
		/// <summary>
		/// 色の構成要素
		/// </summary>
		enum class COMPONENTS
		{
			ALPHA,
			RED,
			GREEN,
			BLUE,
		};
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <remarks>
		/// 初期値は非透明の白0xFFFFFFFF
		/// </remarks>
		Color();

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="colorCode">カラーコード</param>
		Color(DWORD colorCode);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="alpha">透過度</param>
		/// <param name="red">赤</param>
		/// <param name="green">緑</param>
		/// <param name="blue">青</param>
		Color(BYTE alpha, BYTE red, BYTE green, BYTE blue);

		/// <summary>デストラクタ</summary>
		~Color();
		
		/// <summary>
		/// カラーコードを取得する
		/// </summary>
		/// <returns>現在設定されているカラーコード</returns>
		inline DWORD GetColorCode() const
		{
			return D3DCOLOR_ARGB(m_alpha, m_red, m_green, m_blue);
		}
		
		/// <summary>
		/// thisと引数との平均のカラーコードを取得する
		/// </summary>
		/// <param name="colorCode">平均をとるカラーコード</param>
		/// <returns>平均のカラーコード</returns>
		DWORD GetAverageColorCode(DWORD colorCode) const;
		
		/// <summary>
		/// thisと引数との平均のColorクラスを返す
		/// </summary>
		/// <param name="color">平均をとるColorクラス</param>
		/// <returns>平均のカラー</returns>
		Color GetAverage(const Color& color) const;

		/// <summary>
		/// 添え字でアクセスできる色を変える
		/// </summary>
		/// <param name="colorComponent">アクセスする色のCOMPONENTS</param>
		/// <returns>アクセスした色の参照</returns>>
		BYTE& operator[](COMPONENTS colorComponent);
		
		/// <summary>
		/// カラーコードを分解し保存する
		/// </summary>
		/// <param name="colorCode">代入するカラーコード</param>
		/// <returns>thisの参照</returns>
		/// <remarks>
		/// <para>colorCodeの下位バイトからB→G→R→Aの順に1バイトずつ抜き出し、</para>
		/// <para>それぞれ対応するメンバに保存する</para>
		/// </remarks>
		Color& operator=(DWORD colorCode);

		/// <summary>
		/// 引数の色と自身の色を足しその値を返す
		/// </summary>
		/// <param name="rhs">自身と足すColorクラス</param>
		/// <returns>足した結果のColorクラス</returns>
		const Color operator+(const Color& rhs) const;

		/// <summary>
		/// 引数の色と自身の色を足しその値を返す
		/// </summary>
		/// <param name="rhs">自身と足すヵラーコード</param>
		/// <returns>足した結果のColorクラス</returns>
		const Color operator+(DWORD rhs) const;

		/// <summary>
		/// 引数の色と自身の色を引きその値を返す
		/// </summary>
		/// <param name="rhs">自身と引くColorクラス</param>
		/// <returns>引いた結果のColorクラス</returns>
		const Color operator-(const Color& rhs) const;

		const Color operator-(DWORD rhs) const;

		/// <summary>
		/// 引数の色と自身の色を足しその値を代入する
		/// </summary>
		/// <param name="rhs">自身と足すColorクラス</param>
		/// <returns>thisの参照</returns>
		const Color operator+=(const Color& rhs);

		/// <summary>
		/// 引数の色と自身の色を足しその値を代入する
		/// </summary>
		/// <param name="rhs">自身と足すカラーコード</param>
		/// <returns>thisの参照</returns>
		const Color operator+=(DWORD rhs);

		/// <summary>
		/// 引数の色と自身の色を引きその値を代入する
		/// </summary>
		/// <param name="rhs">自身と引くColorクラス</param>
		/// <returns>thisの参照</returns>
		const Color operator-=(const Color& rhs);

		const Color operator-=(DWORD rhs);

		/// <summary>
		/// 引数の値でメンバを掛ける
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>掛けた後の結果のColorクラス</returns>
		const Color operator*(float rhs) const;

		/// <summary>
		/// 引数の値でメンバを掛けその値を代入する
		/// </summary>
		/// <param name="rhs">掛ける際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator*=(float rhs);

		/// <summary>
		/// 引数の値でメンバを割る
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>割った後の結果のColorクラス</returns>
		const Color operator/(int rhs) const;

		/// <summary>
		/// 引数の値でメンバを割りその値を代入する
		/// </summary>
		/// <param name="rhs">割る際の値</param>
		/// <returns>thisの参照</returns>
		Color& operator/=(int rhs);

	private:
		BYTE m_alpha;
		BYTE m_red;
		BYTE m_green;
		BYTE m_blue;

		BYTE Normalize(int componentValue) const;
		BYTE Normalize(float componentValue) const;
	};
}

#endif //! COLOR_H
