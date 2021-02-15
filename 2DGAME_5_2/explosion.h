#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

#endif