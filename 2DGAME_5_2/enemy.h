#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

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
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	ENEMYSTATE state;		//状態
	int nCounterState;		//状態カウンター
	int nLife;				//体力
}ENEMY;

//----------------------
//マクロ定義
//----------------------
#define MAX_ENEMYTYPE (255)
#define ENEMYLIFE1 (100)	//敵１の体力

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