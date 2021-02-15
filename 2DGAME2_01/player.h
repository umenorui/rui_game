#pragma once
#ifndef _PLAYER_H_
#define _PLATER_H_
#include "main.h"
#include "input.h"
#include "bullet.h"

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;
	int nCnterAnim;			//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNO.
	int nPatternnSeatAnim;		//
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	int nLife;				//体力
}PLAYER;

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
#endif
