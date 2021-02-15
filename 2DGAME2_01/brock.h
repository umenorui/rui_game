#pragma once
#ifndef _BROCK_H_
#define _BROCK_H_
#include "main.h"

//----------------------
//�}�N����`
//----------------------
#define MAX_BROCKTYPE (255)

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}BROCK;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitBrock(void);
void UninitBrock(void);
void UpdateBrock(void);
void DrawBrock(void);
void SetBrock(D3DXVECTOR3 pos, int nType);

#endif