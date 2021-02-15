#pragma once
#ifndef _ENEMY2_H_
#define _ENEMY2_H_
#include "main.h"

//----------------------
//マクロ定義
//----------------------
#define MAX_ENEMY2TYPE (255)
#define ENEMY2LIFE1 (50)	//敵1の体力

//----------------------
//敵の状態
//----------------------
typedef enum
{
	ENEMY2STATE_NORMAL = 0,	//通常状態
	ENEMY2STATE_DAMAGE,		//ダメージ状態
	EMENYS2TATE_MAX
}ENEMY2STATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//
	int nCnterAnim;			//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNO.
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	ENEMY2STATE state;		//状態
	int nCounterState;		//状態カウンター
	int nLife;				//体力
}ENEMY2;

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
void SetEnemy2(D3DXVECTOR3 pos, int nType);
ENEMY2 *GetEnemy2(void);
bool HitEnemy2(int nIdx, int nDamage);

#endif