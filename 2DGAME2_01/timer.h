#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

#define MAX_TIMER (8)//�X�R�A�̍ő吔

//===============
//�e�̍\����
//===============
typedef struct
{
	int nTimer;//����
}TIMER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
TIMER *GetTimer(void);
void AddTimer(int nValue);
#endif
