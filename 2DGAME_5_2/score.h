#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"

//スコアの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bUse;			//使用しているかどうか
}SCORE;

//----------------------
//マクロ定義
//----------------------
#define MAX_SCORE (8)

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

#endif
