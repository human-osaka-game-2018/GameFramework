#ifndef COLLISION_H
#define COLLISION_H

#include "RectSize.h"
#include "Degree.h"
#include "Vertices.h"
#include "algorithm.h"

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	namespace collision
	{
		/// <summary>
		/// 矩形の辺のベクトルを作成する
		/// </summary>
		/// <param name="pSideVecs">作成したベクトルを入れる構造体の先頭アドレス</param>
		/// <param name="pVertices">頂点情報構造体の先頭アドレス</param>
		void CreateSideVectors(D3DXVECTOR2* pSideVecs, const CustomVertex* pVertices);

		/// <summary>
		/// 矩形の4頂点から引数の点へのベクトルを作成する
		/// </summary>
		/// <param name="pVecsVToP">作成したベクトルを入れる構造体の先頭アドレス</param>
		/// <param name="pVertices">頂点情報構造体の先頭アドレス</param>
		/// <param name="pos">点</param>
		void CreateVectorsVertexToPos(D3DXVECTOR2* pVecsVToP, const CustomVertex* pVertices, const D3DXVECTOR3& pos);

		/// <summary>
		/// 矩形の辺のベクトルと矩形の頂点から任意の点へのベクトルを用いその点が矩形の内側にあるかを判断する
		/// </summary>
		/// <param name="pSideVecs">矩形の辺のベクトルの先頭アドレス</param>
		/// <param name="pVecsVToP">矩形の頂点から任意の点へのベクトルのアドレス</param>
		/// <returns>中にあればtrue</returns>
		bool IsInner(const D3DXVECTOR2* pSideVecs, const D3DXVECTOR2 * pVecsVToP);

		/// <summary>
		/// 既定となる矩形から見てもう一つの矩形の頂点が内包されているかを判定する
		/// </summary>
		/// <param name="pBaseVertices">既定となる頂点情報構造体の先頭アドレス</param>
		/// <param name="pVertices">頂点情報構造体の先頭アドレス</param>
		/// <returns>中にあればtrue</returns>
		bool Collides(const CustomVertex* pBaseVertices, const CustomVertex* pVertices);

		/// <summary>
		/// 矩形と矩形の当たり判定チェック
		/// </summary>
		/// <param name="rectA">矩形クラス</param>
		/// <param name="rectB">矩形クラス</param>
		/// <returns>当たっていたらtrue</returns>
		bool Collides(Vertices& rectA, Vertices& rectB);

		/// <summary>
		/// 矩形と点の当たり判定チェック
		/// </summary>
		/// <param name="rect">矩形クラス</param>
		/// <param name="pos">点</param>
		/// <returns>当たっていたらtrue</returns>
		bool IsInner(Vertices& rect, D3DXVECTOR3& pos);

		/// <summary>
		/// 円と円の当たり判定チェック
		/// </summary>
		/// <param name="circleA">矩形クラス</param>
		/// <param name="circleB">矩形クラス</param>
		/// <returns>当たっていたらtrue</returns>
		bool Collides(Vertices& circleA, Vertices& circleB);

		/// <summary>
		/// 円と点の当たり判定チェック
		/// </summary>
		/// <param name="circle">矩形クラス</param>
		/// <param name="Pos">点</param>
		/// <returns>当たっていたらtrue</returns>
		bool Collides(Vertices& circle, D3DXVECTOR3& Pos);
	}
}

#endif //!COLLISION_H
