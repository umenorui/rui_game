#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//----------------------
//敵の状態
//----------------------
typedef enum
{
	BULLETTYPE_PLAYER = 0,	
	BULLETTYPE_ENEMY,
	BELlETTYPE_MAX
}BULLETTYPE;

//----------------------
//マクロ定義
//----------------------
#define BULLETDAMAGE (10)	//弾のダメージ

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,int nLife);

#endif
