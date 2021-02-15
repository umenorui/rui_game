#pragma once
#ifndef _BROCK_H_
#define _BROCK_H_
#include "main.h"

//----------------------
//マクロ定義
//----------------------
#define MAX_BROCKTYPE (255)

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	int nType;				//種類
	bool bUse;				//使用しているかどうか
}BROCK;

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitBrock(void);
void UninitBrock(void);
void UpdateBrock(void);
void DrawBrock(void);
void SetBrock(D3DXVECTOR3 pos, int nType);

#endif