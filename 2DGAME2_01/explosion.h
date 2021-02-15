#pragma once
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//----------------------
//�}�N����`
//----------------------
#define MAX_EXPLOSION (256)	//�G�̎��

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);

#endif
