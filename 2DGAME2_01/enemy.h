#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//----------------------
//マクロ定義
//----------------------
#define MAX_ENEMYTYPE (255)
#define ENEMYLIFE1 (100)	//敵1の体力
#define ENEMYLIFE2 (200)	//敵2の体力
#define ENEMYLIFE3 (300)	//敵3の体力

//----------------------
//敵の状態
//----------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	EMENYSTATE_MAX
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//
	int nCnterAnim;			//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNO.
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態カウンター
	int nLife;				//体力
}ENEMY;

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);

#endif
