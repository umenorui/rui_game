#pragma once
#ifndef _PLAYER_H_
#define _PLATER_H_
#include "main.h"
#include "input.h"
#include "bullet.h"

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;
	int nCnterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��NO.
	int nPatternnSeatAnim;		//
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	int nLife;				//�̗�
}PLAYER;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
#endif
