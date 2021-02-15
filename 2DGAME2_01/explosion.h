#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//----------------------
//マクロ定義
//----------------------
#define MAX_EXPLOSION (256)	//敵の種類

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

#endif
