#pragma once
#ifndef _ENEMY2_H_
#define _ENEMY2_H_
#include "main.h"

//----------------------
//�}�N����`
//----------------------
#define MAX_ENEMY2TYPE (255)
#define ENEMY2LIFE1 (50)	//�G1�̗̑�

//----------------------
//�G�̏��
//----------------------
typedef enum
{
	ENEMY2STATE_NORMAL = 0,	//�ʏ���
	ENEMY2STATE_DAMAGE,		//�_���[�W���
	EMENYS2TATE_MAX
}ENEMY2STATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//
	int nCnterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��NO.
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	ENEMY2STATE state;		//���
	int nCounterState;		//��ԃJ�E���^�[
	int nLife;				//�̗�
}ENEMY2;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
void SetEnemy2(D3DXVECTOR3 pos, int nType);
ENEMY2 *GetEnemy2(void);
bool HitEnemy2(int nIdx, int nDamage);

#endif