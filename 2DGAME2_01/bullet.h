#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//----------------------
//�G�̏��
//----------------------
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BELlETTYPE_MAX
}BULLETTYPE;

//----------------------
//�}�N����`
//----------------------
#define BULLETDAMAGE (10)		//�e�̃_���[�W
#define MAX_BULLET (256)		//�ő�e��
#define MAX_BULLETTIPE (2)	//�e�̎�ސ�
#define MAX_ENEMY (256)			//�G�̐�

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife);

#endif
