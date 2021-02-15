#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//----------------------
//�|�[�Y���j���[
//----------------------
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	//�R���e�B�j���[
	PAUSE_MENU_RETRY,			//���g���C
	PAUSE_MENU_QUIT,			//�I��
	PAUSE_MENU_MAX
}PAUSE_MENU;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif
