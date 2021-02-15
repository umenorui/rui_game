#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//----------------------
//�}�N����`
//----------------------
#define MAX_ENEMYTYPE (255)
#define ENEMYLIFE1 (100)	//�G1�̗̑�
#define ENEMYLIFE2 (200)	//�G2�̗̑�
#define ENEMYLIFE3 (300)	//�G3�̗̑�

//----------------------
//�G�̏��
//----------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	EMENYSTATE_MAX
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//
	int nCnterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��NO.
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	ENEMYSTATE state;		//���
	int nCounterState;		//��ԃJ�E���^�[
	int nLife;				//�̗�
}ENEMY;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
ENEMY *GetEnemy(void);
bool HitEnemy(int nIdx, int nDamage);

#endif
