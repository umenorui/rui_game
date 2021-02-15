#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"

//�X�R�A�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	bool bUse;			//�g�p���Ă��邩�ǂ���
}SCORE;

//----------------------
//�}�N����`
//----------------------
#define MAX_SCORE (8)

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nValue);

#endif
